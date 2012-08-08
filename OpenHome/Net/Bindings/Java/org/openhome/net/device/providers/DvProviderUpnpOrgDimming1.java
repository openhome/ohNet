package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderUpnpOrgDimming1
{

    /**
     * Set the value of the LoadLevelStatus property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyLoadLevelStatus(long aValue);

    /**
     * Get a copy of the value of the LoadLevelStatus property
     *
     * @return value of the LoadLevelStatus property.
     */
    public long getPropertyLoadLevelStatus();

    /**
     * Set the value of the StepDelta property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyStepDelta(long aValue);

    /**
     * Get a copy of the value of the StepDelta property
     *
     * @return value of the StepDelta property.
     */
    public long getPropertyStepDelta();

    /**
     * Set the value of the RampRate property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyRampRate(long aValue);

    /**
     * Get a copy of the value of the RampRate property
     *
     * @return value of the RampRate property.
     */
    public long getPropertyRampRate();

    /**
     * Set the value of the IsRamping property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyIsRamping(boolean aValue);

    /**
     * Get a copy of the value of the IsRamping property
     *
     * @return value of the IsRamping property.
     */
    public boolean getPropertyIsRamping();

    /**
     * Set the value of the RampPaused property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyRampPaused(boolean aValue);

    /**
     * Get a copy of the value of the RampPaused property
     *
     * @return value of the RampPaused property.
     */
    public boolean getPropertyRampPaused();
        
}

/**
 * Provider for the upnp.org:Dimming:1 UPnP service.
 */
public class DvProviderUpnpOrgDimming1 extends DvProvider implements IDvProviderUpnpOrgDimming1
{

    public class GetOnEffectParameters
    {
        private String iRetOnEffect;
        private long iRetOnEffectLevel;

        public GetOnEffectParameters(
            String aRetOnEffect,
            long aRetOnEffectLevel
        )
        {
            iRetOnEffect = aRetOnEffect;
            iRetOnEffectLevel = aRetOnEffectLevel;
        }
        public String getRetOnEffect()
        {
            return iRetOnEffect;
        }
        public long getRetOnEffectLevel()
        {
            return iRetOnEffectLevel;
        }
    }

    private IDvInvocationListener iDelegateSetLoadLevelTarget;
    private IDvInvocationListener iDelegateGetLoadLevelTarget;
    private IDvInvocationListener iDelegateGetLoadLevelStatus;
    private IDvInvocationListener iDelegateSetOnEffectLevel;
    private IDvInvocationListener iDelegateSetOnEffect;
    private IDvInvocationListener iDelegateGetOnEffectParameters;
    private IDvInvocationListener iDelegateStepUp;
    private IDvInvocationListener iDelegateStepDown;
    private IDvInvocationListener iDelegateStartRampUp;
    private IDvInvocationListener iDelegateStartRampDown;
    private IDvInvocationListener iDelegateStopRamp;
    private IDvInvocationListener iDelegateStartRampToLevel;
    private IDvInvocationListener iDelegateSetStepDelta;
    private IDvInvocationListener iDelegateGetStepDelta;
    private IDvInvocationListener iDelegateSetRampRate;
    private IDvInvocationListener iDelegateGetRampRate;
    private IDvInvocationListener iDelegatePauseRamp;
    private IDvInvocationListener iDelegateResumeRamp;
    private IDvInvocationListener iDelegateGetIsRamping;
    private IDvInvocationListener iDelegateGetRampPaused;
    private IDvInvocationListener iDelegateGetRampTime;
    private PropertyUint iPropertyLoadLevelStatus;
    private PropertyUint iPropertyStepDelta;
    private PropertyUint iPropertyRampRate;
    private PropertyBool iPropertyIsRamping;
    private PropertyBool iPropertyRampPaused;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderUpnpOrgDimming1(DvDevice aDevice)
    {
        super(aDevice, "upnp.org", "Dimming", 1);
    }

    /**
     * Enable the LoadLevelStatus property.
     */
    public void enablePropertyLoadLevelStatus()
    {
        iPropertyLoadLevelStatus = new PropertyUint(new ParameterUint("LoadLevelStatus", 0, 100));
        addProperty(iPropertyLoadLevelStatus);
    }

    /**
     * Enable the StepDelta property.
     */
    public void enablePropertyStepDelta()
    {
        iPropertyStepDelta = new PropertyUint(new ParameterUint("StepDelta", 1, 100));
        addProperty(iPropertyStepDelta);
    }

    /**
     * Enable the RampRate property.
     */
    public void enablePropertyRampRate()
    {
        iPropertyRampRate = new PropertyUint(new ParameterUint("RampRate", 0, 100));
        addProperty(iPropertyRampRate);
    }

    /**
     * Enable the IsRamping property.
     */
    public void enablePropertyIsRamping()
    {
        iPropertyIsRamping = new PropertyBool(new ParameterBool("IsRamping"));
        addProperty(iPropertyIsRamping);
    }

    /**
     * Enable the RampPaused property.
     */
    public void enablePropertyRampPaused()
    {
        iPropertyRampPaused = new PropertyBool(new ParameterBool("RampPaused"));
        addProperty(iPropertyRampPaused);
    }

    /**
     * Set the value of the LoadLevelStatus property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyLoadLevelStatus(long aValue)
    {
        return setPropertyUint(iPropertyLoadLevelStatus, aValue);
    }

    /**
     * Get a copy of the value of the LoadLevelStatus property
     *
     * @return  value of the LoadLevelStatus property.
     */
    public long getPropertyLoadLevelStatus()
    {
        return iPropertyLoadLevelStatus.getValue();
    }

    /**
     * Set the value of the StepDelta property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyStepDelta(long aValue)
    {
        return setPropertyUint(iPropertyStepDelta, aValue);
    }

    /**
     * Get a copy of the value of the StepDelta property
     *
     * @return  value of the StepDelta property.
     */
    public long getPropertyStepDelta()
    {
        return iPropertyStepDelta.getValue();
    }

    /**
     * Set the value of the RampRate property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyRampRate(long aValue)
    {
        return setPropertyUint(iPropertyRampRate, aValue);
    }

    /**
     * Get a copy of the value of the RampRate property
     *
     * @return  value of the RampRate property.
     */
    public long getPropertyRampRate()
    {
        return iPropertyRampRate.getValue();
    }

    /**
     * Set the value of the IsRamping property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyIsRamping(boolean aValue)
    {
        return setPropertyBool(iPropertyIsRamping, aValue);
    }

    /**
     * Get a copy of the value of the IsRamping property
     *
     * @return  value of the IsRamping property.
     */
    public boolean getPropertyIsRamping()
    {
        return iPropertyIsRamping.getValue();
    }

    /**
     * Set the value of the RampPaused property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyRampPaused(boolean aValue)
    {
        return setPropertyBool(iPropertyRampPaused, aValue);
    }

    /**
     * Get a copy of the value of the RampPaused property
     *
     * @return  value of the RampPaused property.
     */
    public boolean getPropertyRampPaused()
    {
        return iPropertyRampPaused.getValue();
    }

    /**
     * Signal that the action SetLoadLevelTarget is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetLoadLevelTarget must be overridden if this is called.
     */      
    protected void enableActionSetLoadLevelTarget()
    {
        Action action = new Action("SetLoadLevelTarget");
        action.addInputParameter(new ParameterUint("newLoadlevelTarget", 0, 100));
        iDelegateSetLoadLevelTarget = new DoSetLoadLevelTarget();
        enableAction(action, iDelegateSetLoadLevelTarget);
    }

    /**
     * Signal that the action GetLoadLevelTarget is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetLoadLevelTarget must be overridden if this is called.
     */      
    protected void enableActionGetLoadLevelTarget()
    {
        Action action = new Action("GetLoadLevelTarget");
        action.addOutputParameter(new ParameterUint("GetLoadlevelTarget", 0, 100));
        iDelegateGetLoadLevelTarget = new DoGetLoadLevelTarget();
        enableAction(action, iDelegateGetLoadLevelTarget);
    }

    /**
     * Signal that the action GetLoadLevelStatus is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetLoadLevelStatus must be overridden if this is called.
     */      
    protected void enableActionGetLoadLevelStatus()
    {
        Action action = new Action("GetLoadLevelStatus");
        action.addOutputParameter(new ParameterRelated("retLoadlevelStatus", iPropertyLoadLevelStatus));
        iDelegateGetLoadLevelStatus = new DoGetLoadLevelStatus();
        enableAction(action, iDelegateGetLoadLevelStatus);
    }

    /**
     * Signal that the action SetOnEffectLevel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetOnEffectLevel must be overridden if this is called.
     */      
    protected void enableActionSetOnEffectLevel()
    {
        Action action = new Action("SetOnEffectLevel");
        action.addInputParameter(new ParameterUint("newOnEffectLevel", 0, 100));
        iDelegateSetOnEffectLevel = new DoSetOnEffectLevel();
        enableAction(action, iDelegateSetOnEffectLevel);
    }

    /**
     * Signal that the action SetOnEffect is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetOnEffect must be overridden if this is called.
     */      
    protected void enableActionSetOnEffect()
    {
        Action action = new Action("SetOnEffect");        List<String> allowedValues = new LinkedList<String>();
        allowedValues.add("OnEffectLevel");
        allowedValues.add("LastSetting");
        allowedValues.add("Default");
        action.addInputParameter(new ParameterString("newOnEffect", allowedValues));
        allowedValues.clear();
        iDelegateSetOnEffect = new DoSetOnEffect();
        enableAction(action, iDelegateSetOnEffect);
    }

    /**
     * Signal that the action GetOnEffectParameters is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetOnEffectParameters must be overridden if this is called.
     */      
    protected void enableActionGetOnEffectParameters()
    {
        Action action = new Action("GetOnEffectParameters");        List<String> allowedValues = new LinkedList<String>();
        allowedValues.add("OnEffectLevel");
        allowedValues.add("LastSetting");
        allowedValues.add("Default");
        action.addOutputParameter(new ParameterString("retOnEffect", allowedValues));
        allowedValues.clear();
        action.addOutputParameter(new ParameterUint("retOnEffectLevel", 0, 100));
        iDelegateGetOnEffectParameters = new DoGetOnEffectParameters();
        enableAction(action, iDelegateGetOnEffectParameters);
    }

    /**
     * Signal that the action StepUp is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * StepUp must be overridden if this is called.
     */      
    protected void enableActionStepUp()
    {
        Action action = new Action("StepUp");
        iDelegateStepUp = new DoStepUp();
        enableAction(action, iDelegateStepUp);
    }

    /**
     * Signal that the action StepDown is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * StepDown must be overridden if this is called.
     */      
    protected void enableActionStepDown()
    {
        Action action = new Action("StepDown");
        iDelegateStepDown = new DoStepDown();
        enableAction(action, iDelegateStepDown);
    }

    /**
     * Signal that the action StartRampUp is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * StartRampUp must be overridden if this is called.
     */      
    protected void enableActionStartRampUp()
    {
        Action action = new Action("StartRampUp");
        iDelegateStartRampUp = new DoStartRampUp();
        enableAction(action, iDelegateStartRampUp);
    }

    /**
     * Signal that the action StartRampDown is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * StartRampDown must be overridden if this is called.
     */      
    protected void enableActionStartRampDown()
    {
        Action action = new Action("StartRampDown");
        iDelegateStartRampDown = new DoStartRampDown();
        enableAction(action, iDelegateStartRampDown);
    }

    /**
     * Signal that the action StopRamp is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * StopRamp must be overridden if this is called.
     */      
    protected void enableActionStopRamp()
    {
        Action action = new Action("StopRamp");
        iDelegateStopRamp = new DoStopRamp();
        enableAction(action, iDelegateStopRamp);
    }

    /**
     * Signal that the action StartRampToLevel is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * StartRampToLevel must be overridden if this is called.
     */      
    protected void enableActionStartRampToLevel()
    {
        Action action = new Action("StartRampToLevel");
        action.addInputParameter(new ParameterUint("newLoadLevelTarget", 0, 100));
        action.addInputParameter(new ParameterUint("newRampTime"));
        iDelegateStartRampToLevel = new DoStartRampToLevel();
        enableAction(action, iDelegateStartRampToLevel);
    }

    /**
     * Signal that the action SetStepDelta is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetStepDelta must be overridden if this is called.
     */      
    protected void enableActionSetStepDelta()
    {
        Action action = new Action("SetStepDelta");
        action.addInputParameter(new ParameterRelated("newStepDelta", iPropertyStepDelta));
        iDelegateSetStepDelta = new DoSetStepDelta();
        enableAction(action, iDelegateSetStepDelta);
    }

    /**
     * Signal that the action GetStepDelta is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetStepDelta must be overridden if this is called.
     */      
    protected void enableActionGetStepDelta()
    {
        Action action = new Action("GetStepDelta");
        action.addOutputParameter(new ParameterRelated("retStepDelta", iPropertyStepDelta));
        iDelegateGetStepDelta = new DoGetStepDelta();
        enableAction(action, iDelegateGetStepDelta);
    }

    /**
     * Signal that the action SetRampRate is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetRampRate must be overridden if this is called.
     */      
    protected void enableActionSetRampRate()
    {
        Action action = new Action("SetRampRate");
        action.addInputParameter(new ParameterRelated("newRampRate", iPropertyRampRate));
        iDelegateSetRampRate = new DoSetRampRate();
        enableAction(action, iDelegateSetRampRate);
    }

    /**
     * Signal that the action GetRampRate is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRampRate must be overridden if this is called.
     */      
    protected void enableActionGetRampRate()
    {
        Action action = new Action("GetRampRate");
        action.addOutputParameter(new ParameterRelated("retRampRate", iPropertyRampRate));
        iDelegateGetRampRate = new DoGetRampRate();
        enableAction(action, iDelegateGetRampRate);
    }

    /**
     * Signal that the action PauseRamp is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PauseRamp must be overridden if this is called.
     */      
    protected void enableActionPauseRamp()
    {
        Action action = new Action("PauseRamp");
        iDelegatePauseRamp = new DoPauseRamp();
        enableAction(action, iDelegatePauseRamp);
    }

    /**
     * Signal that the action ResumeRamp is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ResumeRamp must be overridden if this is called.
     */      
    protected void enableActionResumeRamp()
    {
        Action action = new Action("ResumeRamp");
        iDelegateResumeRamp = new DoResumeRamp();
        enableAction(action, iDelegateResumeRamp);
    }

    /**
     * Signal that the action GetIsRamping is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetIsRamping must be overridden if this is called.
     */      
    protected void enableActionGetIsRamping()
    {
        Action action = new Action("GetIsRamping");
        action.addOutputParameter(new ParameterRelated("retIsRamping", iPropertyIsRamping));
        iDelegateGetIsRamping = new DoGetIsRamping();
        enableAction(action, iDelegateGetIsRamping);
    }

    /**
     * Signal that the action GetRampPaused is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRampPaused must be overridden if this is called.
     */      
    protected void enableActionGetRampPaused()
    {
        Action action = new Action("GetRampPaused");
        action.addOutputParameter(new ParameterRelated("retRampPaused", iPropertyRampPaused));
        iDelegateGetRampPaused = new DoGetRampPaused();
        enableAction(action, iDelegateGetRampPaused);
    }

    /**
     * Signal that the action GetRampTime is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRampTime must be overridden if this is called.
     */      
    protected void enableActionGetRampTime()
    {
        Action action = new Action("GetRampTime");
        action.addOutputParameter(new ParameterUint("retRampTime"));
        iDelegateGetRampTime = new DoGetRampTime();
        enableAction(action, iDelegateGetRampTime);
    }

    /**
     * SetLoadLevelTarget action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetLoadLevelTarget action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetLoadLevelTarget} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param anewLoadlevelTarget
     */
    protected void setLoadLevelTarget(IDvInvocation aInvocation, long anewLoadlevelTarget)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetLoadLevelTarget action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetLoadLevelTarget action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetLoadLevelTarget} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long getLoadLevelTarget(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetLoadLevelStatus action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetLoadLevelStatus action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetLoadLevelStatus} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long getLoadLevelStatus(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetOnEffectLevel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetOnEffectLevel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetOnEffectLevel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param anewOnEffectLevel
     */
    protected void setOnEffectLevel(IDvInvocation aInvocation, long anewOnEffectLevel)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetOnEffect action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetOnEffect action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetOnEffect} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param anewOnEffect
     */
    protected void setOnEffect(IDvInvocation aInvocation, String anewOnEffect)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetOnEffectParameters action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetOnEffectParameters action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetOnEffectParameters} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected GetOnEffectParameters getOnEffectParameters(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * StepUp action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * StepUp action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionStepUp} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected void stepUp(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * StepDown action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * StepDown action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionStepDown} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected void stepDown(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * StartRampUp action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * StartRampUp action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionStartRampUp} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected void startRampUp(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * StartRampDown action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * StartRampDown action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionStartRampDown} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected void startRampDown(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * StopRamp action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * StopRamp action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionStopRamp} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected void stopRamp(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * StartRampToLevel action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * StartRampToLevel action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionStartRampToLevel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param anewLoadLevelTarget
     * @param anewRampTime
     */
    protected void startRampToLevel(IDvInvocation aInvocation, long anewLoadLevelTarget, long anewRampTime)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetStepDelta action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetStepDelta action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetStepDelta} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param anewStepDelta
     */
    protected void setStepDelta(IDvInvocation aInvocation, long anewStepDelta)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetStepDelta action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetStepDelta action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetStepDelta} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long getStepDelta(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetRampRate action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetRampRate action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetRampRate} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param anewRampRate
     */
    protected void setRampRate(IDvInvocation aInvocation, long anewRampRate)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRampRate action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRampRate action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRampRate} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long getRampRate(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PauseRamp action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PauseRamp action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPauseRamp} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected void pauseRamp(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * ResumeRamp action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ResumeRamp action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionResumeRamp} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected void resumeRamp(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetIsRamping action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetIsRamping action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetIsRamping} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected boolean getIsRamping(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRampPaused action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRampPaused action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRampPaused} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected boolean getRampPaused(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRampTime action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRampTime action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRampTime} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long getRampTime(IDvInvocation aInvocation)
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


    private class DoSetLoadLevelTarget implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long newLoadlevelTarget;
            try
            {
                invocation.readStart();
                newLoadlevelTarget = invocation.readUint("newLoadlevelTarget");
                invocation.readEnd();
                setLoadLevelTarget(invocation, newLoadlevelTarget);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetLoadLevelTarget");
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

    private class DoGetLoadLevelTarget implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long getLoadlevelTarget;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 getLoadlevelTarget = getLoadLevelTarget(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetLoadLevelTarget");
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
                invocation.writeUint("GetLoadlevelTarget", getLoadlevelTarget);
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

    private class DoGetLoadLevelStatus implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long retLoadlevelStatus;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 retLoadlevelStatus = getLoadLevelStatus(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetLoadLevelStatus");
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
                invocation.writeUint("retLoadlevelStatus", retLoadlevelStatus);
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

    private class DoSetOnEffectLevel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long newOnEffectLevel;
            try
            {
                invocation.readStart();
                newOnEffectLevel = invocation.readUint("newOnEffectLevel");
                invocation.readEnd();
                setOnEffectLevel(invocation, newOnEffectLevel);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetOnEffectLevel");
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

    private class DoSetOnEffect implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String newOnEffect;
            try
            {
                invocation.readStart();
                newOnEffect = invocation.readString("newOnEffect");
                invocation.readEnd();
                setOnEffect(invocation, newOnEffect);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetOnEffect");
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

    private class DoGetOnEffectParameters implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String retOnEffect;
            long retOnEffectLevel;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            GetOnEffectParameters outArgs = getOnEffectParameters(invocation);
            retOnEffect = outArgs.getRetOnEffect();
            retOnEffectLevel = outArgs.getRetOnEffectLevel();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetOnEffectParameters");
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
                invocation.writeString("retOnEffect", retOnEffect);
                invocation.writeUint("retOnEffectLevel", retOnEffectLevel);
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

    private class DoStepUp implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                stepUp(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "StepUp");
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

    private class DoStepDown implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                stepDown(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "StepDown");
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

    private class DoStartRampUp implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                startRampUp(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "StartRampUp");
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

    private class DoStartRampDown implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                startRampDown(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "StartRampDown");
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

    private class DoStopRamp implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                stopRamp(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "StopRamp");
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

    private class DoStartRampToLevel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long newLoadLevelTarget;
            long newRampTime;
            try
            {
                invocation.readStart();
                newLoadLevelTarget = invocation.readUint("newLoadLevelTarget");
                newRampTime = invocation.readUint("newRampTime");
                invocation.readEnd();
                startRampToLevel(invocation, newLoadLevelTarget, newRampTime);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "StartRampToLevel");
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

    private class DoSetStepDelta implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long newStepDelta;
            try
            {
                invocation.readStart();
                newStepDelta = invocation.readUint("newStepDelta");
                invocation.readEnd();
                setStepDelta(invocation, newStepDelta);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetStepDelta");
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

    private class DoGetStepDelta implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long retStepDelta;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 retStepDelta = getStepDelta(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetStepDelta");
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
                invocation.writeUint("retStepDelta", retStepDelta);
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

    private class DoSetRampRate implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long newRampRate;
            try
            {
                invocation.readStart();
                newRampRate = invocation.readUint("newRampRate");
                invocation.readEnd();
                setRampRate(invocation, newRampRate);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetRampRate");
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

    private class DoGetRampRate implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long retRampRate;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 retRampRate = getRampRate(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRampRate");
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
                invocation.writeUint("retRampRate", retRampRate);
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

    private class DoPauseRamp implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                pauseRamp(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "PauseRamp");
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

    private class DoResumeRamp implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            try
            {
                invocation.readStart();
                invocation.readEnd();
                resumeRamp(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "ResumeRamp");
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

    private class DoGetIsRamping implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean retIsRamping;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 retIsRamping = getIsRamping(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetIsRamping");
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
                invocation.writeBool("retIsRamping", retIsRamping);
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

    private class DoGetRampPaused implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean retRampPaused;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 retRampPaused = getRampPaused(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRampPaused");
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
                invocation.writeBool("retRampPaused", retRampPaused);
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

    private class DoGetRampTime implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long retRampTime;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 retRampTime = getRampTime(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRampTime");
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
                invocation.writeUint("retRampTime", retRampTime);
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

