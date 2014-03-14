package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyUpnpOrgDimming1.*;
import org.openhome.net.core.*;

    
interface ICpProxyUpnpOrgDimming1 extends ICpProxy
{
    public void syncSetLoadLevelTarget(long aNewLoadlevelTarget);
    public void beginSetLoadLevelTarget(long aNewLoadlevelTarget, ICpProxyListener aCallback);
    public void endSetLoadLevelTarget(long aAsyncHandle);
    public long syncGetLoadLevelTarget();
    public void beginGetLoadLevelTarget(ICpProxyListener aCallback);
    public long endGetLoadLevelTarget(long aAsyncHandle);
    public long syncGetLoadLevelStatus();
    public void beginGetLoadLevelStatus(ICpProxyListener aCallback);
    public long endGetLoadLevelStatus(long aAsyncHandle);
    public void syncSetOnEffectLevel(long aNewOnEffectLevel);
    public void beginSetOnEffectLevel(long aNewOnEffectLevel, ICpProxyListener aCallback);
    public void endSetOnEffectLevel(long aAsyncHandle);
    public void syncSetOnEffect(String aNewOnEffect);
    public void beginSetOnEffect(String aNewOnEffect, ICpProxyListener aCallback);
    public void endSetOnEffect(long aAsyncHandle);
    public GetOnEffectParameters syncGetOnEffectParameters();
    public void beginGetOnEffectParameters(ICpProxyListener aCallback);
    public GetOnEffectParameters endGetOnEffectParameters(long aAsyncHandle);
    public void syncStepUp();
    public void beginStepUp(ICpProxyListener aCallback);
    public void endStepUp(long aAsyncHandle);
    public void syncStepDown();
    public void beginStepDown(ICpProxyListener aCallback);
    public void endStepDown(long aAsyncHandle);
    public void syncStartRampUp();
    public void beginStartRampUp(ICpProxyListener aCallback);
    public void endStartRampUp(long aAsyncHandle);
    public void syncStartRampDown();
    public void beginStartRampDown(ICpProxyListener aCallback);
    public void endStartRampDown(long aAsyncHandle);
    public void syncStopRamp();
    public void beginStopRamp(ICpProxyListener aCallback);
    public void endStopRamp(long aAsyncHandle);
    public void syncStartRampToLevel(long aNewLoadLevelTarget, long aNewRampTime);
    public void beginStartRampToLevel(long aNewLoadLevelTarget, long aNewRampTime, ICpProxyListener aCallback);
    public void endStartRampToLevel(long aAsyncHandle);
    public void syncSetStepDelta(long aNewStepDelta);
    public void beginSetStepDelta(long aNewStepDelta, ICpProxyListener aCallback);
    public void endSetStepDelta(long aAsyncHandle);
    public long syncGetStepDelta();
    public void beginGetStepDelta(ICpProxyListener aCallback);
    public long endGetStepDelta(long aAsyncHandle);
    public void syncSetRampRate(long aNewRampRate);
    public void beginSetRampRate(long aNewRampRate, ICpProxyListener aCallback);
    public void endSetRampRate(long aAsyncHandle);
    public long syncGetRampRate();
    public void beginGetRampRate(ICpProxyListener aCallback);
    public long endGetRampRate(long aAsyncHandle);
    public void syncPauseRamp();
    public void beginPauseRamp(ICpProxyListener aCallback);
    public void endPauseRamp(long aAsyncHandle);
    public void syncResumeRamp();
    public void beginResumeRamp(ICpProxyListener aCallback);
    public void endResumeRamp(long aAsyncHandle);
    public boolean syncGetIsRamping();
    public void beginGetIsRamping(ICpProxyListener aCallback);
    public boolean endGetIsRamping(long aAsyncHandle);
    public boolean syncGetRampPaused();
    public void beginGetRampPaused(ICpProxyListener aCallback);
    public boolean endGetRampPaused(long aAsyncHandle);
    public long syncGetRampTime();
    public void beginGetRampTime(ICpProxyListener aCallback);
    public long endGetRampTime(long aAsyncHandle);
    public void setPropertyLoadLevelStatusChanged(IPropertyChangeListener aLoadLevelStatusChanged);
    public long getPropertyLoadLevelStatus();
    public void setPropertyStepDeltaChanged(IPropertyChangeListener aStepDeltaChanged);
    public long getPropertyStepDelta();
    public void setPropertyRampRateChanged(IPropertyChangeListener aRampRateChanged);
    public long getPropertyRampRate();
    public void setPropertyIsRampingChanged(IPropertyChangeListener aIsRampingChanged);
    public boolean getPropertyIsRamping();
    public void setPropertyRampPausedChanged(IPropertyChangeListener aRampPausedChanged);
    public boolean getPropertyRampPaused();
}

class SyncSetLoadLevelTargetUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncSetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetLoadLevelTarget(aAsyncHandle);
        
    }
}

class SyncGetLoadLevelTargetUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;
    private long iGetLoadlevelTarget;

    public SyncGetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    public long getGetLoadlevelTarget()
    {
        return iGetLoadlevelTarget;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetLoadLevelTarget(aAsyncHandle);
        
        iGetLoadlevelTarget = result;
    }
}

class SyncGetLoadLevelStatusUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;
    private long iRetLoadlevelStatus;

    public SyncGetLoadLevelStatusUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    public long getRetLoadlevelStatus()
    {
        return iRetLoadlevelStatus;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetLoadLevelStatus(aAsyncHandle);
        
        iRetLoadlevelStatus = result;
    }
}

class SyncSetOnEffectLevelUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncSetOnEffectLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetOnEffectLevel(aAsyncHandle);
        
    }
}

class SyncSetOnEffectUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncSetOnEffectUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetOnEffect(aAsyncHandle);
        
    }
}

class SyncGetOnEffectParametersUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;
    private String iRetOnEffect;
    private long iRetOnEffectLevel;

    public SyncGetOnEffectParametersUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    public String getRetOnEffect()
    {
        return iRetOnEffect;
    }
    public long getRetOnEffectLevel()
    {
        return iRetOnEffectLevel;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetOnEffectParameters result = iService.endGetOnEffectParameters(aAsyncHandle);
        
        iRetOnEffect = result.getRetOnEffect();
        iRetOnEffectLevel = result.getRetOnEffectLevel();
    }
}

class SyncStepUpUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncStepUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStepUp(aAsyncHandle);
        
    }
}

class SyncStepDownUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncStepDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStepDown(aAsyncHandle);
        
    }
}

class SyncStartRampUpUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncStartRampUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStartRampUp(aAsyncHandle);
        
    }
}

class SyncStartRampDownUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncStartRampDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStartRampDown(aAsyncHandle);
        
    }
}

class SyncStopRampUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncStopRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStopRamp(aAsyncHandle);
        
    }
}

class SyncStartRampToLevelUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncStartRampToLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endStartRampToLevel(aAsyncHandle);
        
    }
}

class SyncSetStepDeltaUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncSetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetStepDelta(aAsyncHandle);
        
    }
}

class SyncGetStepDeltaUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;
    private long iRetStepDelta;

    public SyncGetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    public long getRetStepDelta()
    {
        return iRetStepDelta;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetStepDelta(aAsyncHandle);
        
        iRetStepDelta = result;
    }
}

class SyncSetRampRateUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncSetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetRampRate(aAsyncHandle);
        
    }
}

class SyncGetRampRateUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;
    private long iRetRampRate;

    public SyncGetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    public long getRetRampRate()
    {
        return iRetRampRate;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetRampRate(aAsyncHandle);
        
        iRetRampRate = result;
    }
}

class SyncPauseRampUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncPauseRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endPauseRamp(aAsyncHandle);
        
    }
}

class SyncResumeRampUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;

    public SyncResumeRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endResumeRamp(aAsyncHandle);
        
    }
}

class SyncGetIsRampingUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;
    private boolean iRetIsRamping;

    public SyncGetIsRampingUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getRetIsRamping()
    {
        return iRetIsRamping;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endGetIsRamping(aAsyncHandle);
        
        iRetIsRamping = result;
    }
}

class SyncGetRampPausedUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;
    private boolean iRetRampPaused;

    public SyncGetRampPausedUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getRetRampPaused()
    {
        return iRetRampPaused;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endGetRampPaused(aAsyncHandle);
        
        iRetRampPaused = result;
    }
}

class SyncGetRampTimeUpnpOrgDimming1 extends SyncProxyAction
{
    private CpProxyUpnpOrgDimming1 iService;
    private long iRetRampTime;

    public SyncGetRampTimeUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
    {
        iService = aProxy;
    }
    public long getRetRampTime()
    {
        return iRetRampTime;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetRampTime(aAsyncHandle);
        
        iRetRampTime = result;
    }
}

/**
 * Proxy for the upnp.org:Dimming:1 UPnP service
 */
public class CpProxyUpnpOrgDimming1 extends CpProxy implements ICpProxyUpnpOrgDimming1
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

    private Action iActionSetLoadLevelTarget;
    private Action iActionGetLoadLevelTarget;
    private Action iActionGetLoadLevelStatus;
    private Action iActionSetOnEffectLevel;
    private Action iActionSetOnEffect;
    private Action iActionGetOnEffectParameters;
    private Action iActionStepUp;
    private Action iActionStepDown;
    private Action iActionStartRampUp;
    private Action iActionStartRampDown;
    private Action iActionStopRamp;
    private Action iActionStartRampToLevel;
    private Action iActionSetStepDelta;
    private Action iActionGetStepDelta;
    private Action iActionSetRampRate;
    private Action iActionGetRampRate;
    private Action iActionPauseRamp;
    private Action iActionResumeRamp;
    private Action iActionGetIsRamping;
    private Action iActionGetRampPaused;
    private Action iActionGetRampTime;
    private PropertyUint iLoadLevelStatus;
    private PropertyUint iStepDelta;
    private PropertyUint iRampRate;
    private PropertyBool iIsRamping;
    private PropertyBool iRampPaused;
    private IPropertyChangeListener iLoadLevelStatusChanged;
    private IPropertyChangeListener iStepDeltaChanged;
    private IPropertyChangeListener iRampRateChanged;
    private IPropertyChangeListener iIsRampingChanged;
    private IPropertyChangeListener iRampPausedChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyUpnpOrgDimming1(CpDevice aDevice)
    {
        super("schemas-upnp-org", "Dimming", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionSetLoadLevelTarget = new Action("SetLoadLevelTarget");
        param = new ParameterUint("newLoadlevelTarget", 0, 100);
        iActionSetLoadLevelTarget.addInputParameter(param);

        iActionGetLoadLevelTarget = new Action("GetLoadLevelTarget");
        param = new ParameterUint("GetLoadlevelTarget", 0, 100);
        iActionGetLoadLevelTarget.addOutputParameter(param);

        iActionGetLoadLevelStatus = new Action("GetLoadLevelStatus");
        param = new ParameterUint("retLoadlevelStatus", 0, 100);
        iActionGetLoadLevelStatus.addOutputParameter(param);

        iActionSetOnEffectLevel = new Action("SetOnEffectLevel");
        param = new ParameterUint("newOnEffectLevel", 0, 100);
        iActionSetOnEffectLevel.addInputParameter(param);

        iActionSetOnEffect = new Action("SetOnEffect");
        allowedValues.add("OnEffectLevel");
        allowedValues.add("LastSetting");
        allowedValues.add("Default");
        param = new ParameterString("newOnEffect", allowedValues);
        iActionSetOnEffect.addInputParameter(param);
        allowedValues.clear();

        iActionGetOnEffectParameters = new Action("GetOnEffectParameters");
        allowedValues.add("OnEffectLevel");
        allowedValues.add("LastSetting");
        allowedValues.add("Default");
        param = new ParameterString("retOnEffect", allowedValues);
        iActionGetOnEffectParameters.addOutputParameter(param);
        allowedValues.clear();
        param = new ParameterUint("retOnEffectLevel", 0, 100);
        iActionGetOnEffectParameters.addOutputParameter(param);

        iActionStepUp = new Action("StepUp");

        iActionStepDown = new Action("StepDown");

        iActionStartRampUp = new Action("StartRampUp");

        iActionStartRampDown = new Action("StartRampDown");

        iActionStopRamp = new Action("StopRamp");

        iActionStartRampToLevel = new Action("StartRampToLevel");
        param = new ParameterUint("newLoadLevelTarget", 0, 100);
        iActionStartRampToLevel.addInputParameter(param);
        param = new ParameterUint("newRampTime");
        iActionStartRampToLevel.addInputParameter(param);

        iActionSetStepDelta = new Action("SetStepDelta");
        param = new ParameterUint("newStepDelta", 1, 100);
        iActionSetStepDelta.addInputParameter(param);

        iActionGetStepDelta = new Action("GetStepDelta");
        param = new ParameterUint("retStepDelta", 1, 100);
        iActionGetStepDelta.addOutputParameter(param);

        iActionSetRampRate = new Action("SetRampRate");
        param = new ParameterUint("newRampRate", 0, 100);
        iActionSetRampRate.addInputParameter(param);

        iActionGetRampRate = new Action("GetRampRate");
        param = new ParameterUint("retRampRate", 0, 100);
        iActionGetRampRate.addOutputParameter(param);

        iActionPauseRamp = new Action("PauseRamp");

        iActionResumeRamp = new Action("ResumeRamp");

        iActionGetIsRamping = new Action("GetIsRamping");
        param = new ParameterBool("retIsRamping");
        iActionGetIsRamping.addOutputParameter(param);

        iActionGetRampPaused = new Action("GetRampPaused");
        param = new ParameterBool("retRampPaused");
        iActionGetRampPaused.addOutputParameter(param);

        iActionGetRampTime = new Action("GetRampTime");
        param = new ParameterUint("retRampTime");
        iActionGetRampTime.addOutputParameter(param);

        iLoadLevelStatusChanged = new PropertyChangeListener();
        iLoadLevelStatus = new PropertyUint("LoadLevelStatus",
            new PropertyChangeListener() {
                public void notifyChange() {
                    loadLevelStatusPropertyChanged();
                }
            }
        );
        addProperty(iLoadLevelStatus);
        iStepDeltaChanged = new PropertyChangeListener();
        iStepDelta = new PropertyUint("StepDelta",
            new PropertyChangeListener() {
                public void notifyChange() {
                    stepDeltaPropertyChanged();
                }
            }
        );
        addProperty(iStepDelta);
        iRampRateChanged = new PropertyChangeListener();
        iRampRate = new PropertyUint("RampRate",
            new PropertyChangeListener() {
                public void notifyChange() {
                    rampRatePropertyChanged();
                }
            }
        );
        addProperty(iRampRate);
        iIsRampingChanged = new PropertyChangeListener();
        iIsRamping = new PropertyBool("IsRamping",
            new PropertyChangeListener() {
                public void notifyChange() {
                    isRampingPropertyChanged();
                }
            }
        );
        addProperty(iIsRamping);
        iRampPausedChanged = new PropertyChangeListener();
        iRampPaused = new PropertyBool("RampPaused",
            new PropertyChangeListener() {
                public void notifyChange() {
                    rampPausedPropertyChanged();
                }
            }
        );
        addProperty(iRampPaused);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetLoadLevelTarget(long aNewLoadlevelTarget)
    {
        SyncSetLoadLevelTargetUpnpOrgDimming1 sync = new SyncSetLoadLevelTargetUpnpOrgDimming1(this);
        beginSetLoadLevelTarget(aNewLoadlevelTarget, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetLoadLevelTarget}.
     * 
     * @param aNewLoadlevelTarget
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetLoadLevelTarget(long aNewLoadlevelTarget, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetLoadLevelTarget, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetLoadLevelTarget.getInputParameter(inIndex++), aNewLoadlevelTarget));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetLoadLevelTarget} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetLoadLevelTarget} method.
     */
    public void endSetLoadLevelTarget(long aAsyncHandle)
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
    public long syncGetLoadLevelTarget()
    {
        SyncGetLoadLevelTargetUpnpOrgDimming1 sync = new SyncGetLoadLevelTargetUpnpOrgDimming1(this);
        beginGetLoadLevelTarget(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getGetLoadlevelTarget();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetLoadLevelTarget}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetLoadLevelTarget(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetLoadLevelTarget, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetLoadLevelTarget.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetLoadLevelTarget} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetLoadLevelTarget} method.
     * @return the result of the previously invoked action.
     */
    public long endGetLoadLevelTarget(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long getLoadlevelTarget = Invocation.getOutputUint(aAsyncHandle, index++);
        return getLoadlevelTarget;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetLoadLevelStatus()
    {
        SyncGetLoadLevelStatusUpnpOrgDimming1 sync = new SyncGetLoadLevelStatusUpnpOrgDimming1(this);
        beginGetLoadLevelStatus(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getRetLoadlevelStatus();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetLoadLevelStatus}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetLoadLevelStatus(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetLoadLevelStatus, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetLoadLevelStatus.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetLoadLevelStatus} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetLoadLevelStatus} method.
     * @return the result of the previously invoked action.
     */
    public long endGetLoadLevelStatus(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long retLoadlevelStatus = Invocation.getOutputUint(aAsyncHandle, index++);
        return retLoadlevelStatus;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetOnEffectLevel(long aNewOnEffectLevel)
    {
        SyncSetOnEffectLevelUpnpOrgDimming1 sync = new SyncSetOnEffectLevelUpnpOrgDimming1(this);
        beginSetOnEffectLevel(aNewOnEffectLevel, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetOnEffectLevel}.
     * 
     * @param aNewOnEffectLevel
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetOnEffectLevel(long aNewOnEffectLevel, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetOnEffectLevel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetOnEffectLevel.getInputParameter(inIndex++), aNewOnEffectLevel));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetOnEffectLevel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetOnEffectLevel} method.
     */
    public void endSetOnEffectLevel(long aAsyncHandle)
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
     */
    public void syncSetOnEffect(String aNewOnEffect)
    {
        SyncSetOnEffectUpnpOrgDimming1 sync = new SyncSetOnEffectUpnpOrgDimming1(this);
        beginSetOnEffect(aNewOnEffect, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetOnEffect}.
     * 
     * @param aNewOnEffect
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetOnEffect(String aNewOnEffect, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetOnEffect, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionSetOnEffect.getInputParameter(inIndex++), aNewOnEffect));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetOnEffect} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetOnEffect} method.
     */
    public void endSetOnEffect(long aAsyncHandle)
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
    public GetOnEffectParameters syncGetOnEffectParameters()
    {
        SyncGetOnEffectParametersUpnpOrgDimming1 sync = new SyncGetOnEffectParametersUpnpOrgDimming1(this);
        beginGetOnEffectParameters(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetOnEffectParameters(
            sync.getRetOnEffect(),
            sync.getRetOnEffectLevel()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetOnEffectParameters}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetOnEffectParameters(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetOnEffectParameters, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetOnEffectParameters.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetOnEffectParameters.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetOnEffectParameters} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetOnEffectParameters} method.
     * @return the result of the previously invoked action.
     */
    public GetOnEffectParameters endGetOnEffectParameters(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String retOnEffect = Invocation.getOutputString(aAsyncHandle, index++);
        long retOnEffectLevel = Invocation.getOutputUint(aAsyncHandle, index++);
        return new GetOnEffectParameters(
            retOnEffect,
            retOnEffectLevel
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncStepUp()
    {
        SyncStepUpUpnpOrgDimming1 sync = new SyncStepUpUpnpOrgDimming1(this);
        beginStepUp(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStepUp}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStepUp(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStepUp, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStepUp} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStepUp} method.
     */
    public void endStepUp(long aAsyncHandle)
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
     */
    public void syncStepDown()
    {
        SyncStepDownUpnpOrgDimming1 sync = new SyncStepDownUpnpOrgDimming1(this);
        beginStepDown(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStepDown}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStepDown(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStepDown, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStepDown} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStepDown} method.
     */
    public void endStepDown(long aAsyncHandle)
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
     */
    public void syncStartRampUp()
    {
        SyncStartRampUpUpnpOrgDimming1 sync = new SyncStartRampUpUpnpOrgDimming1(this);
        beginStartRampUp(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStartRampUp}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStartRampUp(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStartRampUp, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStartRampUp} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStartRampUp} method.
     */
    public void endStartRampUp(long aAsyncHandle)
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
     */
    public void syncStartRampDown()
    {
        SyncStartRampDownUpnpOrgDimming1 sync = new SyncStartRampDownUpnpOrgDimming1(this);
        beginStartRampDown(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStartRampDown}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStartRampDown(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStartRampDown, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStartRampDown} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStartRampDown} method.
     */
    public void endStartRampDown(long aAsyncHandle)
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
     */
    public void syncStopRamp()
    {
        SyncStopRampUpnpOrgDimming1 sync = new SyncStopRampUpnpOrgDimming1(this);
        beginStopRamp(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStopRamp}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStopRamp(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStopRamp, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStopRamp} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStopRamp} method.
     */
    public void endStopRamp(long aAsyncHandle)
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
     */
    public void syncStartRampToLevel(long aNewLoadLevelTarget, long aNewRampTime)
    {
        SyncStartRampToLevelUpnpOrgDimming1 sync = new SyncStartRampToLevelUpnpOrgDimming1(this);
        beginStartRampToLevel(aNewLoadLevelTarget, aNewRampTime, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStartRampToLevel}.
     * 
     * @param aNewLoadLevelTarget
     * @param aNewRampTime
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStartRampToLevel(long aNewLoadLevelTarget, long aNewRampTime, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStartRampToLevel, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionStartRampToLevel.getInputParameter(inIndex++), aNewLoadLevelTarget));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionStartRampToLevel.getInputParameter(inIndex++), aNewRampTime));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStartRampToLevel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStartRampToLevel} method.
     */
    public void endStartRampToLevel(long aAsyncHandle)
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
     */
    public void syncSetStepDelta(long aNewStepDelta)
    {
        SyncSetStepDeltaUpnpOrgDimming1 sync = new SyncSetStepDeltaUpnpOrgDimming1(this);
        beginSetStepDelta(aNewStepDelta, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetStepDelta}.
     * 
     * @param aNewStepDelta
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetStepDelta(long aNewStepDelta, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetStepDelta, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetStepDelta.getInputParameter(inIndex++), aNewStepDelta));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetStepDelta} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetStepDelta} method.
     */
    public void endSetStepDelta(long aAsyncHandle)
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
    public long syncGetStepDelta()
    {
        SyncGetStepDeltaUpnpOrgDimming1 sync = new SyncGetStepDeltaUpnpOrgDimming1(this);
        beginGetStepDelta(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getRetStepDelta();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetStepDelta}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetStepDelta(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetStepDelta, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetStepDelta.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetStepDelta} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetStepDelta} method.
     * @return the result of the previously invoked action.
     */
    public long endGetStepDelta(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long retStepDelta = Invocation.getOutputUint(aAsyncHandle, index++);
        return retStepDelta;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetRampRate(long aNewRampRate)
    {
        SyncSetRampRateUpnpOrgDimming1 sync = new SyncSetRampRateUpnpOrgDimming1(this);
        beginSetRampRate(aNewRampRate, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetRampRate}.
     * 
     * @param aNewRampRate
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetRampRate(long aNewRampRate, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetRampRate, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetRampRate.getInputParameter(inIndex++), aNewRampRate));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetRampRate} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetRampRate} method.
     */
    public void endSetRampRate(long aAsyncHandle)
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
    public long syncGetRampRate()
    {
        SyncGetRampRateUpnpOrgDimming1 sync = new SyncGetRampRateUpnpOrgDimming1(this);
        beginGetRampRate(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getRetRampRate();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRampRate}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRampRate(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRampRate, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetRampRate.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRampRate} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRampRate} method.
     * @return the result of the previously invoked action.
     */
    public long endGetRampRate(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long retRampRate = Invocation.getOutputUint(aAsyncHandle, index++);
        return retRampRate;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncPauseRamp()
    {
        SyncPauseRampUpnpOrgDimming1 sync = new SyncPauseRampUpnpOrgDimming1(this);
        beginPauseRamp(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPauseRamp}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPauseRamp(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPauseRamp, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPauseRamp} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginPauseRamp} method.
     */
    public void endPauseRamp(long aAsyncHandle)
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
     */
    public void syncResumeRamp()
    {
        SyncResumeRampUpnpOrgDimming1 sync = new SyncResumeRampUpnpOrgDimming1(this);
        beginResumeRamp(sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endResumeRamp}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginResumeRamp(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionResumeRamp, aCallback);
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginResumeRamp} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginResumeRamp} method.
     */
    public void endResumeRamp(long aAsyncHandle)
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
    public boolean syncGetIsRamping()
    {
        SyncGetIsRampingUpnpOrgDimming1 sync = new SyncGetIsRampingUpnpOrgDimming1(this);
        beginGetIsRamping(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getRetIsRamping();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetIsRamping}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetIsRamping(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetIsRamping, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionGetIsRamping.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetIsRamping} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetIsRamping} method.
     * @return the result of the previously invoked action.
     */
    public boolean endGetIsRamping(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        boolean retIsRamping = Invocation.getOutputBool(aAsyncHandle, index++);
        return retIsRamping;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public boolean syncGetRampPaused()
    {
        SyncGetRampPausedUpnpOrgDimming1 sync = new SyncGetRampPausedUpnpOrgDimming1(this);
        beginGetRampPaused(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getRetRampPaused();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRampPaused}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRampPaused(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRampPaused, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionGetRampPaused.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRampPaused} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRampPaused} method.
     * @return the result of the previously invoked action.
     */
    public boolean endGetRampPaused(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        boolean retRampPaused = Invocation.getOutputBool(aAsyncHandle, index++);
        return retRampPaused;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetRampTime()
    {
        SyncGetRampTimeUpnpOrgDimming1 sync = new SyncGetRampTimeUpnpOrgDimming1(this);
        beginGetRampTime(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getRetRampTime();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRampTime}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRampTime(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRampTime, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetRampTime.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRampTime} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRampTime} method.
     * @return the result of the previously invoked action.
     */
    public long endGetRampTime(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long retRampTime = Invocation.getOutputUint(aAsyncHandle, index++);
        return retRampTime;
    }
        
    /**
     * Set a delegate to be run when the LoadLevelStatus state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgDimming1 instance will not overlap.
     *
     * @param aLoadLevelStatusChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyLoadLevelStatusChanged(IPropertyChangeListener aLoadLevelStatusChanged)
    {
        synchronized (iPropertyLock)
        {
            iLoadLevelStatusChanged = aLoadLevelStatusChanged;
        }
    }

    private void loadLevelStatusPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iLoadLevelStatusChanged);
        }
    }
    /**
     * Set a delegate to be run when the StepDelta state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgDimming1 instance will not overlap.
     *
     * @param aStepDeltaChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyStepDeltaChanged(IPropertyChangeListener aStepDeltaChanged)
    {
        synchronized (iPropertyLock)
        {
            iStepDeltaChanged = aStepDeltaChanged;
        }
    }

    private void stepDeltaPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iStepDeltaChanged);
        }
    }
    /**
     * Set a delegate to be run when the RampRate state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgDimming1 instance will not overlap.
     *
     * @param aRampRateChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyRampRateChanged(IPropertyChangeListener aRampRateChanged)
    {
        synchronized (iPropertyLock)
        {
            iRampRateChanged = aRampRateChanged;
        }
    }

    private void rampRatePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iRampRateChanged);
        }
    }
    /**
     * Set a delegate to be run when the IsRamping state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgDimming1 instance will not overlap.
     *
     * @param aIsRampingChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyIsRampingChanged(IPropertyChangeListener aIsRampingChanged)
    {
        synchronized (iPropertyLock)
        {
            iIsRampingChanged = aIsRampingChanged;
        }
    }

    private void isRampingPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iIsRampingChanged);
        }
    }
    /**
     * Set a delegate to be run when the RampPaused state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgDimming1 instance will not overlap.
     *
     * @param aRampPausedChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyRampPausedChanged(IPropertyChangeListener aRampPausedChanged)
    {
        synchronized (iPropertyLock)
        {
            iRampPausedChanged = aRampPausedChanged;
        }
    }

    private void rampPausedPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iRampPausedChanged);
        }
    }

    /**
     * Query the value of the LoadLevelStatus property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the LoadLevelStatus property.
     */
    public long getPropertyLoadLevelStatus()
    {
        propertyReadLock();
        long val = iLoadLevelStatus.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the StepDelta property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the StepDelta property.
     */
    public long getPropertyStepDelta()
    {
        propertyReadLock();
        long val = iStepDelta.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the RampRate property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the RampRate property.
     */
    public long getPropertyRampRate()
    {
        propertyReadLock();
        long val = iRampRate.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the IsRamping property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the IsRamping property.
     */
    public boolean getPropertyIsRamping()
    {
        propertyReadLock();
        boolean val = iIsRamping.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the RampPaused property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the RampPaused property.
     */
    public boolean getPropertyRampPaused()
    {
        propertyReadLock();
        boolean val = iRampPaused.getValue();
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
            iActionSetLoadLevelTarget.destroy();
            iActionGetLoadLevelTarget.destroy();
            iActionGetLoadLevelStatus.destroy();
            iActionSetOnEffectLevel.destroy();
            iActionSetOnEffect.destroy();
            iActionGetOnEffectParameters.destroy();
            iActionStepUp.destroy();
            iActionStepDown.destroy();
            iActionStartRampUp.destroy();
            iActionStartRampDown.destroy();
            iActionStopRamp.destroy();
            iActionStartRampToLevel.destroy();
            iActionSetStepDelta.destroy();
            iActionGetStepDelta.destroy();
            iActionSetRampRate.destroy();
            iActionGetRampRate.destroy();
            iActionPauseRamp.destroy();
            iActionResumeRamp.destroy();
            iActionGetIsRamping.destroy();
            iActionGetRampPaused.destroy();
            iActionGetRampTime.destroy();
            iLoadLevelStatus.destroy();
            iStepDelta.destroy();
            iRampRate.destroy();
            iIsRamping.destroy();
            iRampPaused.destroy();
        }
    }
}

