using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Zapp.Core;
using Zapp.ControlPoint;

namespace Zapp.ControlPoint.Proxies
{
    public interface ICpProxyUpnpOrgDimming1 : ICpProxy, IDisposable
    {
        void SyncSetLoadLevelTarget(uint aNewLoadlevelTarget);
        void BeginSetLoadLevelTarget(uint aNewLoadlevelTarget, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetLoadLevelTarget(IntPtr aAsyncHandle);
        void SyncGetLoadLevelTarget(out uint aGetLoadlevelTarget);
        void BeginGetLoadLevelTarget(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLoadLevelTarget(IntPtr aAsyncHandle, out uint aGetLoadlevelTarget);
        void SyncGetLoadLevelStatus(out uint aRetLoadlevelStatus);
        void BeginGetLoadLevelStatus(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetLoadLevelStatus(IntPtr aAsyncHandle, out uint aRetLoadlevelStatus);
        void SyncSetOnEffectLevel(uint aNewOnEffectLevel);
        void BeginSetOnEffectLevel(uint aNewOnEffectLevel, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetOnEffectLevel(IntPtr aAsyncHandle);
        void SyncSetOnEffect(String aNewOnEffect);
        void BeginSetOnEffect(String aNewOnEffect, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetOnEffect(IntPtr aAsyncHandle);
        void SyncGetOnEffectParameters(out String aRetOnEffect, out uint aRetOnEffectLevel);
        void BeginGetOnEffectParameters(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetOnEffectParameters(IntPtr aAsyncHandle, out String aRetOnEffect, out uint aRetOnEffectLevel);
        void SyncStepUp();
        void BeginStepUp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStepUp(IntPtr aAsyncHandle);
        void SyncStepDown();
        void BeginStepDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndStepDown(IntPtr aAsyncHandle);
        void SyncStartRampUp();
        void BeginStartRampUp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampUp(IntPtr aAsyncHandle);
        void SyncStartRampDown();
        void BeginStartRampDown(CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampDown(IntPtr aAsyncHandle);
        void SyncStopRamp();
        void BeginStopRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndStopRamp(IntPtr aAsyncHandle);
        void SyncStartRampToLevel(uint aNewLoadLevelTarget, uint aNewRampTime);
        void BeginStartRampToLevel(uint aNewLoadLevelTarget, uint aNewRampTime, CpProxy.CallbackAsyncComplete aCallback);
        void EndStartRampToLevel(IntPtr aAsyncHandle);
        void SyncSetStepDelta(uint aNewStepDelta);
        void BeginSetStepDelta(uint aNewStepDelta, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetStepDelta(IntPtr aAsyncHandle);
        void SyncGetStepDelta(out uint aRetStepDelta);
        void BeginGetStepDelta(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetStepDelta(IntPtr aAsyncHandle, out uint aRetStepDelta);
        void SyncSetRampRate(uint aNewRampRate);
        void BeginSetRampRate(uint aNewRampRate, CpProxy.CallbackAsyncComplete aCallback);
        void EndSetRampRate(IntPtr aAsyncHandle);
        void SyncGetRampRate(out uint aRetRampRate);
        void BeginGetRampRate(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampRate(IntPtr aAsyncHandle, out uint aRetRampRate);
        void SyncPauseRamp();
        void BeginPauseRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndPauseRamp(IntPtr aAsyncHandle);
        void SyncResumeRamp();
        void BeginResumeRamp(CpProxy.CallbackAsyncComplete aCallback);
        void EndResumeRamp(IntPtr aAsyncHandle);
        void SyncGetIsRamping(out bool aRetIsRamping);
        void BeginGetIsRamping(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetIsRamping(IntPtr aAsyncHandle, out bool aRetIsRamping);
        void SyncGetRampPaused(out bool aRetRampPaused);
        void BeginGetRampPaused(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampPaused(IntPtr aAsyncHandle, out bool aRetRampPaused);
        void SyncGetRampTime(out uint aRetRampTime);
        void BeginGetRampTime(CpProxy.CallbackAsyncComplete aCallback);
        void EndGetRampTime(IntPtr aAsyncHandle, out uint aRetRampTime);
        void SetPropertyLoadLevelStatusChanged(CpProxy.CallbackPropertyChanged aLoadLevelStatusChanged);
        uint PropertyLoadLevelStatus();
        void SetPropertyStepDeltaChanged(CpProxy.CallbackPropertyChanged aStepDeltaChanged);
        uint PropertyStepDelta();
        void SetPropertyRampRateChanged(CpProxy.CallbackPropertyChanged aRampRateChanged);
        uint PropertyRampRate();
        void SetPropertyIsRampingChanged(CpProxy.CallbackPropertyChanged aIsRampingChanged);
        bool PropertyIsRamping();
        void SetPropertyRampPausedChanged(CpProxy.CallbackPropertyChanged aRampPausedChanged);
        bool PropertyRampPaused();
    }

    internal class SyncSetLoadLevelTargetUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetLoadLevelTarget(aAsyncHandle);
        }
    };

    internal class SyncGetLoadLevelTargetUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iGetLoadlevelTarget;

        public SyncGetLoadLevelTargetUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint GetLoadlevelTarget()
        {
            return iGetLoadlevelTarget;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetLoadLevelTarget(aAsyncHandle, out iGetLoadlevelTarget);
        }
    };

    internal class SyncGetLoadLevelStatusUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iRetLoadlevelStatus;

        public SyncGetLoadLevelStatusUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint RetLoadlevelStatus()
        {
            return iRetLoadlevelStatus;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetLoadLevelStatus(aAsyncHandle, out iRetLoadlevelStatus);
        }
    };

    internal class SyncSetOnEffectLevelUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetOnEffectLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetOnEffectLevel(aAsyncHandle);
        }
    };

    internal class SyncSetOnEffectUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetOnEffectUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetOnEffect(aAsyncHandle);
        }
    };

    internal class SyncGetOnEffectParametersUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private String iRetOnEffect;
        private uint iRetOnEffectLevel;

        public SyncGetOnEffectParametersUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public String RetOnEffect()
        {
            return iRetOnEffect;
        }
        public uint RetOnEffectLevel()
        {
            return iRetOnEffectLevel;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetOnEffectParameters(aAsyncHandle, out iRetOnEffect, out iRetOnEffectLevel);
        }
    };

    internal class SyncStepUpUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStepUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStepUp(aAsyncHandle);
        }
    };

    internal class SyncStepDownUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStepDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStepDown(aAsyncHandle);
        }
    };

    internal class SyncStartRampUpUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStartRampUpUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartRampUp(aAsyncHandle);
        }
    };

    internal class SyncStartRampDownUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStartRampDownUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartRampDown(aAsyncHandle);
        }
    };

    internal class SyncStopRampUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStopRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStopRamp(aAsyncHandle);
        }
    };

    internal class SyncStartRampToLevelUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncStartRampToLevelUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndStartRampToLevel(aAsyncHandle);
        }
    };

    internal class SyncSetStepDeltaUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetStepDelta(aAsyncHandle);
        }
    };

    internal class SyncGetStepDeltaUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iRetStepDelta;

        public SyncGetStepDeltaUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint RetStepDelta()
        {
            return iRetStepDelta;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetStepDelta(aAsyncHandle, out iRetStepDelta);
        }
    };

    internal class SyncSetRampRateUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncSetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndSetRampRate(aAsyncHandle);
        }
    };

    internal class SyncGetRampRateUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iRetRampRate;

        public SyncGetRampRateUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint RetRampRate()
        {
            return iRetRampRate;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRampRate(aAsyncHandle, out iRetRampRate);
        }
    };

    internal class SyncPauseRampUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncPauseRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndPauseRamp(aAsyncHandle);
        }
    };

    internal class SyncResumeRampUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;

        public SyncResumeRampUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndResumeRamp(aAsyncHandle);
        }
    };

    internal class SyncGetIsRampingUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private bool iRetIsRamping;

        public SyncGetIsRampingUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public bool RetIsRamping()
        {
            return iRetIsRamping;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetIsRamping(aAsyncHandle, out iRetIsRamping);
        }
    };

    internal class SyncGetRampPausedUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private bool iRetRampPaused;

        public SyncGetRampPausedUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public bool RetRampPaused()
        {
            return iRetRampPaused;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRampPaused(aAsyncHandle, out iRetRampPaused);
        }
    };

    internal class SyncGetRampTimeUpnpOrgDimming1 : SyncProxyAction
    {
        private CpProxyUpnpOrgDimming1 iService;
        private uint iRetRampTime;

        public SyncGetRampTimeUpnpOrgDimming1(CpProxyUpnpOrgDimming1 aProxy)
        {
            iService = aProxy;
        }
        public uint RetRampTime()
        {
            return iRetRampTime;
        }
        protected override void CompleteRequest(IntPtr aAsyncHandle)
        {
            iService.EndGetRampTime(aAsyncHandle, out iRetRampTime);
        }
    };

    /// <summary>
    /// Proxy for the upnp.org:Dimming:1 UPnP service
    /// </summary>
    public class CpProxyUpnpOrgDimming1 : CpProxy, IDisposable, ICpProxyUpnpOrgDimming1
    {
        private Zapp.Core.Action iActionSetLoadLevelTarget;
        private Zapp.Core.Action iActionGetLoadLevelTarget;
        private Zapp.Core.Action iActionGetLoadLevelStatus;
        private Zapp.Core.Action iActionSetOnEffectLevel;
        private Zapp.Core.Action iActionSetOnEffect;
        private Zapp.Core.Action iActionGetOnEffectParameters;
        private Zapp.Core.Action iActionStepUp;
        private Zapp.Core.Action iActionStepDown;
        private Zapp.Core.Action iActionStartRampUp;
        private Zapp.Core.Action iActionStartRampDown;
        private Zapp.Core.Action iActionStopRamp;
        private Zapp.Core.Action iActionStartRampToLevel;
        private Zapp.Core.Action iActionSetStepDelta;
        private Zapp.Core.Action iActionGetStepDelta;
        private Zapp.Core.Action iActionSetRampRate;
        private Zapp.Core.Action iActionGetRampRate;
        private Zapp.Core.Action iActionPauseRamp;
        private Zapp.Core.Action iActionResumeRamp;
        private Zapp.Core.Action iActionGetIsRamping;
        private Zapp.Core.Action iActionGetRampPaused;
        private Zapp.Core.Action iActionGetRampTime;
        private PropertyUint iLoadLevelStatus;
        private PropertyUint iStepDelta;
        private PropertyUint iRampRate;
        private PropertyBool iIsRamping;
        private PropertyBool iRampPaused;
        private CallbackPropertyChanged iLoadLevelStatusChanged;
        private CallbackPropertyChanged iStepDeltaChanged;
        private CallbackPropertyChanged iRampRateChanged;
        private CallbackPropertyChanged iIsRampingChanged;
        private CallbackPropertyChanged iRampPausedChanged;
        private Mutex iPropertyLock;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <remarks>Use CpProxy::[Un]Subscribe() to enable/disable querying of state variable and reporting of their changes.</remarks>
        /// <param name="aDevice">The device to use</param>
        public CpProxyUpnpOrgDimming1(CpDevice aDevice)
            : base("schemas-upnp-org", "Dimming", 1, aDevice)
        {
            Zapp.Core.Parameter param;
            List<String> allowedValues = new List<String>();

            iActionSetLoadLevelTarget = new Zapp.Core.Action("SetLoadLevelTarget");
            param = new ParameterUint("newLoadlevelTarget", 0, 100);
            iActionSetLoadLevelTarget.AddInputParameter(param);

            iActionGetLoadLevelTarget = new Zapp.Core.Action("GetLoadLevelTarget");
            param = new ParameterUint("GetLoadlevelTarget", 0, 100);
            iActionGetLoadLevelTarget.AddOutputParameter(param);

            iActionGetLoadLevelStatus = new Zapp.Core.Action("GetLoadLevelStatus");
            param = new ParameterUint("retLoadlevelStatus", 0, 100);
            iActionGetLoadLevelStatus.AddOutputParameter(param);

            iActionSetOnEffectLevel = new Zapp.Core.Action("SetOnEffectLevel");
            param = new ParameterUint("newOnEffectLevel", 0, 100);
            iActionSetOnEffectLevel.AddInputParameter(param);

            iActionSetOnEffect = new Zapp.Core.Action("SetOnEffect");
            allowedValues.Add("OnEffectLevel");
            allowedValues.Add("LastSetting");
            allowedValues.Add("Default");
            param = new ParameterString("newOnEffect", allowedValues);
            iActionSetOnEffect.AddInputParameter(param);
            allowedValues.Clear();

            iActionGetOnEffectParameters = new Zapp.Core.Action("GetOnEffectParameters");
            allowedValues.Add("OnEffectLevel");
            allowedValues.Add("LastSetting");
            allowedValues.Add("Default");
            param = new ParameterString("retOnEffect", allowedValues);
            iActionGetOnEffectParameters.AddOutputParameter(param);
            allowedValues.Clear();
            param = new ParameterUint("retOnEffectLevel", 0, 100);
            iActionGetOnEffectParameters.AddOutputParameter(param);

            iActionStepUp = new Zapp.Core.Action("StepUp");

            iActionStepDown = new Zapp.Core.Action("StepDown");

            iActionStartRampUp = new Zapp.Core.Action("StartRampUp");

            iActionStartRampDown = new Zapp.Core.Action("StartRampDown");

            iActionStopRamp = new Zapp.Core.Action("StopRamp");

            iActionStartRampToLevel = new Zapp.Core.Action("StartRampToLevel");
            param = new ParameterUint("newLoadLevelTarget", 0, 100);
            iActionStartRampToLevel.AddInputParameter(param);
            param = new ParameterUint("newRampTime");
            iActionStartRampToLevel.AddInputParameter(param);

            iActionSetStepDelta = new Zapp.Core.Action("SetStepDelta");
            param = new ParameterUint("newStepDelta", 1, 100);
            iActionSetStepDelta.AddInputParameter(param);

            iActionGetStepDelta = new Zapp.Core.Action("GetStepDelta");
            param = new ParameterUint("retStepDelta", 1, 100);
            iActionGetStepDelta.AddOutputParameter(param);

            iActionSetRampRate = new Zapp.Core.Action("SetRampRate");
            param = new ParameterUint("newRampRate", 0, 100);
            iActionSetRampRate.AddInputParameter(param);

            iActionGetRampRate = new Zapp.Core.Action("GetRampRate");
            param = new ParameterUint("retRampRate", 0, 100);
            iActionGetRampRate.AddOutputParameter(param);

            iActionPauseRamp = new Zapp.Core.Action("PauseRamp");

            iActionResumeRamp = new Zapp.Core.Action("ResumeRamp");

            iActionGetIsRamping = new Zapp.Core.Action("GetIsRamping");
            param = new ParameterBool("retIsRamping");
            iActionGetIsRamping.AddOutputParameter(param);

            iActionGetRampPaused = new Zapp.Core.Action("GetRampPaused");
            param = new ParameterBool("retRampPaused");
            iActionGetRampPaused.AddOutputParameter(param);

            iActionGetRampTime = new Zapp.Core.Action("GetRampTime");
            param = new ParameterUint("retRampTime");
            iActionGetRampTime.AddOutputParameter(param);

            iLoadLevelStatus = new PropertyUint("LoadLevelStatus", LoadLevelStatusPropertyChanged);
            AddProperty(iLoadLevelStatus);
            iStepDelta = new PropertyUint("StepDelta", StepDeltaPropertyChanged);
            AddProperty(iStepDelta);
            iRampRate = new PropertyUint("RampRate", RampRatePropertyChanged);
            AddProperty(iRampRate);
            iIsRamping = new PropertyBool("IsRamping", IsRampingPropertyChanged);
            AddProperty(iIsRamping);
            iRampPaused = new PropertyBool("RampPaused", RampPausedPropertyChanged);
            AddProperty(iRampPaused);
            
            iPropertyLock = new Mutex();
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="anewLoadlevelTarget"></param>
        public void SyncSetLoadLevelTarget(uint aNewLoadlevelTarget)
        {
            SyncSetLoadLevelTargetUpnpOrgDimming1 sync = new SyncSetLoadLevelTargetUpnpOrgDimming1(this);
            BeginSetLoadLevelTarget(aNewLoadlevelTarget, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetLoadLevelTarget().</remarks>
        /// <param name="anewLoadlevelTarget"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetLoadLevelTarget(uint aNewLoadlevelTarget, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetLoadLevelTarget, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetLoadLevelTarget.InputParameter(inIndex++), aNewLoadlevelTarget));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetLoadLevelTarget(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aGetLoadlevelTarget"></param>
        public void SyncGetLoadLevelTarget(out uint aGetLoadlevelTarget)
        {
            SyncGetLoadLevelTargetUpnpOrgDimming1 sync = new SyncGetLoadLevelTargetUpnpOrgDimming1(this);
            BeginGetLoadLevelTarget(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aGetLoadlevelTarget = sync.GetLoadlevelTarget();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLoadLevelTarget().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetLoadLevelTarget(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetLoadLevelTarget, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetLoadLevelTarget.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aGetLoadlevelTarget"></param>
        public void EndGetLoadLevelTarget(IntPtr aAsyncHandle, out uint aGetLoadlevelTarget)
        {
            uint index = 0;
            aGetLoadlevelTarget = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aretLoadlevelStatus"></param>
        public void SyncGetLoadLevelStatus(out uint aRetLoadlevelStatus)
        {
            SyncGetLoadLevelStatusUpnpOrgDimming1 sync = new SyncGetLoadLevelStatusUpnpOrgDimming1(this);
            BeginGetLoadLevelStatus(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetLoadlevelStatus = sync.RetLoadlevelStatus();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetLoadLevelStatus().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetLoadLevelStatus(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetLoadLevelStatus, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetLoadLevelStatus.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretLoadlevelStatus"></param>
        public void EndGetLoadLevelStatus(IntPtr aAsyncHandle, out uint aRetLoadlevelStatus)
        {
            uint index = 0;
            aRetLoadlevelStatus = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="anewOnEffectLevel"></param>
        public void SyncSetOnEffectLevel(uint aNewOnEffectLevel)
        {
            SyncSetOnEffectLevelUpnpOrgDimming1 sync = new SyncSetOnEffectLevelUpnpOrgDimming1(this);
            BeginSetOnEffectLevel(aNewOnEffectLevel, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetOnEffectLevel().</remarks>
        /// <param name="anewOnEffectLevel"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetOnEffectLevel(uint aNewOnEffectLevel, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetOnEffectLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetOnEffectLevel.InputParameter(inIndex++), aNewOnEffectLevel));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetOnEffectLevel(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="anewOnEffect"></param>
        public void SyncSetOnEffect(String aNewOnEffect)
        {
            SyncSetOnEffectUpnpOrgDimming1 sync = new SyncSetOnEffectUpnpOrgDimming1(this);
            BeginSetOnEffect(aNewOnEffect, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetOnEffect().</remarks>
        /// <param name="anewOnEffect"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetOnEffect(String aNewOnEffect, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetOnEffect, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentString((ParameterString)iActionSetOnEffect.InputParameter(inIndex++), aNewOnEffect));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetOnEffect(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aretOnEffect"></param>
        /// <param name="aretOnEffectLevel"></param>
        public void SyncGetOnEffectParameters(out String aRetOnEffect, out uint aRetOnEffectLevel)
        {
            SyncGetOnEffectParametersUpnpOrgDimming1 sync = new SyncGetOnEffectParametersUpnpOrgDimming1(this);
            BeginGetOnEffectParameters(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetOnEffect = sync.RetOnEffect();
            aRetOnEffectLevel = sync.RetOnEffectLevel();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetOnEffectParameters().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetOnEffectParameters(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetOnEffectParameters, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentString((ParameterString)iActionGetOnEffectParameters.OutputParameter(outIndex++)));
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetOnEffectParameters.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretOnEffect"></param>
        /// <param name="aretOnEffectLevel"></param>
        public void EndGetOnEffectParameters(IntPtr aAsyncHandle, out String aRetOnEffect, out uint aRetOnEffectLevel)
        {
            uint index = 0;
            aRetOnEffect = Invocation.OutputString(aAsyncHandle, index++);
            aRetOnEffectLevel = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncStepUp()
        {
            SyncStepUpUpnpOrgDimming1 sync = new SyncStepUpUpnpOrgDimming1(this);
            BeginStepUp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStepUp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStepUp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStepUp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStepUp(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncStepDown()
        {
            SyncStepDownUpnpOrgDimming1 sync = new SyncStepDownUpnpOrgDimming1(this);
            BeginStepDown(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStepDown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStepDown(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStepDown, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStepDown(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncStartRampUp()
        {
            SyncStartRampUpUpnpOrgDimming1 sync = new SyncStartRampUpUpnpOrgDimming1(this);
            BeginStartRampUp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartRampUp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartRampUp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartRampUp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStartRampUp(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncStartRampDown()
        {
            SyncStartRampDownUpnpOrgDimming1 sync = new SyncStartRampDownUpnpOrgDimming1(this);
            BeginStartRampDown(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartRampDown().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartRampDown(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartRampDown, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStartRampDown(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncStopRamp()
        {
            SyncStopRampUpnpOrgDimming1 sync = new SyncStopRampUpnpOrgDimming1(this);
            BeginStopRamp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStopRamp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStopRamp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStopRamp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStopRamp(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="anewLoadLevelTarget"></param>
        /// <param name="anewRampTime"></param>
        public void SyncStartRampToLevel(uint aNewLoadLevelTarget, uint aNewRampTime)
        {
            SyncStartRampToLevelUpnpOrgDimming1 sync = new SyncStartRampToLevelUpnpOrgDimming1(this);
            BeginStartRampToLevel(aNewLoadLevelTarget, aNewRampTime, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndStartRampToLevel().</remarks>
        /// <param name="anewLoadLevelTarget"></param>
        /// <param name="anewRampTime"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginStartRampToLevel(uint aNewLoadLevelTarget, uint aNewRampTime, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionStartRampToLevel, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionStartRampToLevel.InputParameter(inIndex++), aNewLoadLevelTarget));
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionStartRampToLevel.InputParameter(inIndex++), aNewRampTime));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndStartRampToLevel(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="anewStepDelta"></param>
        public void SyncSetStepDelta(uint aNewStepDelta)
        {
            SyncSetStepDeltaUpnpOrgDimming1 sync = new SyncSetStepDeltaUpnpOrgDimming1(this);
            BeginSetStepDelta(aNewStepDelta, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetStepDelta().</remarks>
        /// <param name="anewStepDelta"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetStepDelta(uint aNewStepDelta, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetStepDelta, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetStepDelta.InputParameter(inIndex++), aNewStepDelta));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetStepDelta(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aretStepDelta"></param>
        public void SyncGetStepDelta(out uint aRetStepDelta)
        {
            SyncGetStepDeltaUpnpOrgDimming1 sync = new SyncGetStepDeltaUpnpOrgDimming1(this);
            BeginGetStepDelta(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetStepDelta = sync.RetStepDelta();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetStepDelta().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetStepDelta(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetStepDelta, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetStepDelta.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretStepDelta"></param>
        public void EndGetStepDelta(IntPtr aAsyncHandle, out uint aRetStepDelta)
        {
            uint index = 0;
            aRetStepDelta = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="anewRampRate"></param>
        public void SyncSetRampRate(uint aNewRampRate)
        {
            SyncSetRampRateUpnpOrgDimming1 sync = new SyncSetRampRateUpnpOrgDimming1(this);
            BeginSetRampRate(aNewRampRate, sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndSetRampRate().</remarks>
        /// <param name="anewRampRate"></param>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginSetRampRate(uint aNewRampRate, CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionSetRampRate, aCallback);
            int inIndex = 0;
            invocation.AddInput(new ArgumentUint((ParameterUint)iActionSetRampRate.InputParameter(inIndex++), aNewRampRate));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndSetRampRate(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aretRampRate"></param>
        public void SyncGetRampRate(out uint aRetRampRate)
        {
            SyncGetRampRateUpnpOrgDimming1 sync = new SyncGetRampRateUpnpOrgDimming1(this);
            BeginGetRampRate(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetRampRate = sync.RetRampRate();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRampRate().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRampRate(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRampRate, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRampRate.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretRampRate"></param>
        public void EndGetRampRate(IntPtr aAsyncHandle, out uint aRetRampRate)
        {
            uint index = 0;
            aRetRampRate = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncPauseRamp()
        {
            SyncPauseRampUpnpOrgDimming1 sync = new SyncPauseRampUpnpOrgDimming1(this);
            BeginPauseRamp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndPauseRamp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginPauseRamp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionPauseRamp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndPauseRamp(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        public void SyncResumeRamp()
        {
            SyncResumeRampUpnpOrgDimming1 sync = new SyncResumeRampUpnpOrgDimming1(this);
            BeginResumeRamp(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndResumeRamp().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginResumeRamp(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionResumeRamp, aCallback);
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        public void EndResumeRamp(IntPtr aAsyncHandle)
        {
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aretIsRamping"></param>
        public void SyncGetIsRamping(out bool aRetIsRamping)
        {
            SyncGetIsRampingUpnpOrgDimming1 sync = new SyncGetIsRampingUpnpOrgDimming1(this);
            BeginGetIsRamping(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetIsRamping = sync.RetIsRamping();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetIsRamping().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetIsRamping(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetIsRamping, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetIsRamping.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretIsRamping"></param>
        public void EndGetIsRamping(IntPtr aAsyncHandle, out bool aRetIsRamping)
        {
            uint index = 0;
            aRetIsRamping = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aretRampPaused"></param>
        public void SyncGetRampPaused(out bool aRetRampPaused)
        {
            SyncGetRampPausedUpnpOrgDimming1 sync = new SyncGetRampPausedUpnpOrgDimming1(this);
            BeginGetRampPaused(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetRampPaused = sync.RetRampPaused();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRampPaused().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRampPaused(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRampPaused, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentBool((ParameterBool)iActionGetRampPaused.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretRampPaused"></param>
        public void EndGetRampPaused(IntPtr aAsyncHandle, out bool aRetRampPaused)
        {
            uint index = 0;
            aRetRampPaused = Invocation.OutputBool(aAsyncHandle, index++);
        }

        /// <summary>
        /// Invoke the action synchronously
        /// </summary>
        /// <remarks>Blocks until the action has been processed
        /// on the device and sets any output arguments</remarks>
        /// <param name="aretRampTime"></param>
        public void SyncGetRampTime(out uint aRetRampTime)
        {
            SyncGetRampTimeUpnpOrgDimming1 sync = new SyncGetRampTimeUpnpOrgDimming1(this);
            BeginGetRampTime(sync.AsyncComplete());
            sync.Wait();
            sync.ReportError();
            aRetRampTime = sync.RetRampTime();
        }

        /// <summary>
        /// Invoke the action asynchronously
        /// </summary>
        /// <remarks>Returns immediately and will run the client-specified callback when the action
        /// later completes.  Any output arguments can then be retrieved by calling
        /// EndGetRampTime().</remarks>
        /// <param name="aCallback">Delegate to run when the action completes.
        /// This is guaranteed to be run but may indicate an error</param>
        public void BeginGetRampTime(CallbackAsyncComplete aCallback)
        {
            Invocation invocation = iService.Invocation(iActionGetRampTime, aCallback);
            int outIndex = 0;
            invocation.AddOutput(new ArgumentUint((ParameterUint)iActionGetRampTime.OutputParameter(outIndex++)));
            iService.InvokeAction(invocation);
        }

        /// <summary>
        /// Retrieve the output arguments from an asynchronously invoked action.
        /// </summary>
        /// <remarks>This may only be called from the callback set in the above Begin function.</remarks>
        /// <param name="aAsyncHandle">Argument passed to the delegate set in the above Begin function</param>
        /// <param name="aretRampTime"></param>
        public void EndGetRampTime(IntPtr aAsyncHandle, out uint aRetRampTime)
        {
            uint index = 0;
            aRetRampTime = Invocation.OutputUint(aAsyncHandle, index++);
        }

        /// <summary>
        /// Set a delegate to be run when the LoadLevelStatus state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aLoadLevelStatusChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyLoadLevelStatusChanged(CallbackPropertyChanged aLoadLevelStatusChanged)
        {
            lock (iPropertyLock)
            {
                iLoadLevelStatusChanged = aLoadLevelStatusChanged;
            }
        }

        private void LoadLevelStatusPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iLoadLevelStatusChanged != null)
                {
                    iLoadLevelStatusChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the StepDelta state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aStepDeltaChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyStepDeltaChanged(CallbackPropertyChanged aStepDeltaChanged)
        {
            lock (iPropertyLock)
            {
                iStepDeltaChanged = aStepDeltaChanged;
            }
        }

        private void StepDeltaPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iStepDeltaChanged != null)
                {
                    iStepDeltaChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the RampRate state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aRampRateChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyRampRateChanged(CallbackPropertyChanged aRampRateChanged)
        {
            lock (iPropertyLock)
            {
                iRampRateChanged = aRampRateChanged;
            }
        }

        private void RampRatePropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iRampRateChanged != null)
                {
                    iRampRateChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the IsRamping state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aIsRampingChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyIsRampingChanged(CallbackPropertyChanged aIsRampingChanged)
        {
            lock (iPropertyLock)
            {
                iIsRampingChanged = aIsRampingChanged;
            }
        }

        private void IsRampingPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iIsRampingChanged != null)
                {
                    iIsRampingChanged();
                }
            }
        }

        /// <summary>
        /// Set a delegate to be run when the RampPaused state variable changes.
        /// </summary>
        /// <remarks>Callbacks may be run in different threads but callbacks for a
        /// CpProxyUpnpOrgDimming1 instance will not overlap.</remarks>
        /// <param name="aRampPausedChanged">The delegate to run when the state variable changes</param>
        public void SetPropertyRampPausedChanged(CallbackPropertyChanged aRampPausedChanged)
        {
            lock (iPropertyLock)
            {
                iRampPausedChanged = aRampPausedChanged;
            }
        }

        private void RampPausedPropertyChanged()
        {
            lock (iPropertyLock)
            {
                if (iRampPausedChanged != null)
                {
                    iRampPausedChanged();
                }
            }
        }

        /// <summary>
        /// Query the value of the LoadLevelStatus property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aLoadLevelStatus">Will be set to the value of the property</param>
        public uint PropertyLoadLevelStatus()
        {
            PropertyReadLock();
            uint val = iLoadLevelStatus.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the StepDelta property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aStepDelta">Will be set to the value of the property</param>
        public uint PropertyStepDelta()
        {
            PropertyReadLock();
            uint val = iStepDelta.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the RampRate property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aRampRate">Will be set to the value of the property</param>
        public uint PropertyRampRate()
        {
            PropertyReadLock();
            uint val = iRampRate.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the IsRamping property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aIsRamping">Will be set to the value of the property</param>
        public bool PropertyIsRamping()
        {
            PropertyReadLock();
            bool val = iIsRamping.Value();
            PropertyReadUnlock();
            return val;
        }

        /// <summary>
        /// Query the value of the RampPaused property.
        /// </summary>
        /// <remarks>This function is threadsafe and can only be called if Subscribe() has been
        /// called and a first eventing callback received more recently than any call
        /// to Unsubscribe().</remarks>
        /// <param name="aRampPaused">Will be set to the value of the property</param>
        public bool PropertyRampPaused()
        {
            PropertyReadLock();
            bool val = iRampPaused.Value();
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

        ~CpProxyUpnpOrgDimming1()
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
                iActionSetLoadLevelTarget.Dispose();
                iActionGetLoadLevelTarget.Dispose();
                iActionGetLoadLevelStatus.Dispose();
                iActionSetOnEffectLevel.Dispose();
                iActionSetOnEffect.Dispose();
                iActionGetOnEffectParameters.Dispose();
                iActionStepUp.Dispose();
                iActionStepDown.Dispose();
                iActionStartRampUp.Dispose();
                iActionStartRampDown.Dispose();
                iActionStopRamp.Dispose();
                iActionStartRampToLevel.Dispose();
                iActionSetStepDelta.Dispose();
                iActionGetStepDelta.Dispose();
                iActionSetRampRate.Dispose();
                iActionGetRampRate.Dispose();
                iActionPauseRamp.Dispose();
                iActionResumeRamp.Dispose();
                iActionGetIsRamping.Dispose();
                iActionGetRampPaused.Dispose();
                iActionGetRampTime.Dispose();
                iLoadLevelStatus.Dispose();
                iStepDelta.Dispose();
                iRampRate.Dispose();
                iIsRamping.Dispose();
                iRampPaused.Dispose();
            }
            if (aDisposing)
            {
                GC.SuppressFinalize(this);
            }
        }
    }
}

