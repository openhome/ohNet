 

/**
 * Proxy for upnp.org:Dimming:1
 */

var ServiceDimming = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/upnp.org-Dimming-1/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Dimming";
	this.iVersion = "1";
	this.iServiceName = "upnp.org-Dimming-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["LoadLevelTarget"] = new ServiceVariable("LoadLevelTarget");
		this.iVariables["LoadLevelStatus"] = new ServiceVariable("LoadLevelStatus");
		this.iVariables["MinLevel"] = new ServiceVariable("MinLevel");
		this.iVariables["OnEffectLevel"] = new ServiceVariable("OnEffectLevel");
		this.iVariables["OnEffect"] = new ServiceVariable("OnEffect");
		this.iVariables["ValidOutputValues"] = new ServiceVariable("ValidOutputValues");
		this.iVariables["StepDelta"] = new ServiceVariable("StepDelta");
		this.iVariables["RampRate"] = new ServiceVariable("RampRate");
		this.iVariables["RampTime"] = new ServiceVariable("RampTime");
		this.iVariables["IsRamping"] = new ServiceVariable("IsRamping");
		this.iVariables["RampPaused"] = new ServiceVariable("RampPaused");
}

ServiceDimming.kOnEffectOnEffectLevel = "OnEffectLevel";
ServiceDimming.kOnEffectLastSetting = "LastSetting";
ServiceDimming.kOnEffectDefault = "Default";

ServiceDimming.prototype.LoadLevelTarget_Changed = function (aStateChangedFunction) {
    this.Variables().LoadLevelTarget.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDimming.prototype.LoadLevelStatus_Changed = function (aStateChangedFunction) {
    this.Variables().LoadLevelStatus.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDimming.prototype.MinLevel_Changed = function (aStateChangedFunction) {
    this.Variables().MinLevel.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDimming.prototype.OnEffectLevel_Changed = function (aStateChangedFunction) {
    this.Variables().OnEffectLevel.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDimming.prototype.OnEffect_Changed = function (aStateChangedFunction) {
    this.Variables().OnEffect.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceDimming.prototype.ValidOutputValues_Changed = function (aStateChangedFunction) {
    this.Variables().ValidOutputValues.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceDimming.prototype.StepDelta_Changed = function (aStateChangedFunction) {
    this.Variables().StepDelta.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDimming.prototype.RampRate_Changed = function (aStateChangedFunction) {
    this.Variables().RampRate.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDimming.prototype.RampTime_Changed = function (aStateChangedFunction) {
    this.Variables().RampTime.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDimming.prototype.IsRamping_Changed = function (aStateChangedFunction) {
    this.Variables().IsRamping.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceDimming.prototype.RampPaused_Changed = function (aStateChangedFunction) {
    this.Variables().RampPaused.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}

ServiceDimming.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceDimming.prototype.Variables = function(){
	return this.iVariables;
}

ServiceDimming.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceDimming.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceDimming.prototype.Udn = function () {
    return this.iUdn;
}

ServiceDimming.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceDimming.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceDimming.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceDimming.prototype.SetLoadLevelTarget = function(newLoadlevelTarget, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetLoadLevelTarget", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("newLoadlevelTarget", newLoadlevelTarget);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.GetLoadLevelTarget = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetLoadLevelTarget", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["GetLoadlevelTarget"] = SoapRequest.ReadIntParameter(result["GetLoadlevelTarget"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.GetLoadLevelStatus = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetLoadLevelStatus", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["retLoadlevelStatus"] = SoapRequest.ReadIntParameter(result["retLoadlevelStatus"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.SetOnEffectLevel = function(newOnEffectLevel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetOnEffectLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("newOnEffectLevel", newOnEffectLevel);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.SetOnEffect = function(newOnEffect, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetOnEffect", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("newOnEffect", newOnEffect);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.GetOnEffectParameters = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetOnEffectParameters", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["retOnEffect"] = SoapRequest.ReadStringParameter(result["retOnEffect"]);	
		result["retOnEffectLevel"] = SoapRequest.ReadIntParameter(result["retOnEffectLevel"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.StepUp = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StepUp", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.StepDown = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StepDown", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.StartRampUp = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StartRampUp", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.StartRampDown = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StartRampDown", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.StopRamp = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StopRamp", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.StartRampToLevel = function(newLoadLevelTarget, newRampTime, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StartRampToLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("newLoadLevelTarget", newLoadLevelTarget);
    request.WriteIntParameter("newRampTime", newRampTime);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.SetStepDelta = function(newStepDelta, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStepDelta", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("newStepDelta", newStepDelta);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.GetStepDelta = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetStepDelta", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["retStepDelta"] = SoapRequest.ReadIntParameter(result["retStepDelta"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.SetRampRate = function(newRampRate, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetRampRate", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("newRampRate", newRampRate);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.GetRampRate = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRampRate", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["retRampRate"] = SoapRequest.ReadIntParameter(result["retRampRate"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.PauseRamp = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("PauseRamp", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.ResumeRamp = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ResumeRamp", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.GetIsRamping = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetIsRamping", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["retIsRamping"] = SoapRequest.ReadBoolParameter(result["retIsRamping"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.GetRampPaused = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRampPaused", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["retRampPaused"] = SoapRequest.ReadBoolParameter(result["retRampPaused"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDimming.prototype.GetRampTime = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRampTime", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["retRampTime"] = SoapRequest.ReadIntParameter(result["retRampTime"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



