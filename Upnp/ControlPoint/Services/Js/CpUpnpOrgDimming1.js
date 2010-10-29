 

/**
 * Proxy for upnp.org:Dimming:1
 */

var ServiceDimming = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Dimming/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Dimming";
	this.iVersion = "1";
	
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

ServiceDimming.prototype.ServiceName = function(){
	return this.iType;
}

ServiceDimming.prototype.Variables = function(){
	return this.iVariables;
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
		result["GetLoadlevelTarget"] = request.ReadIntParameter(result["GetLoadlevelTarget"]);	
	
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
		result["retLoadlevelStatus"] = request.ReadIntParameter(result["retLoadlevelStatus"]);	
	
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
		result["retOnEffect"] = request.ReadStringParameter(result["retOnEffect"]);	
		result["retOnEffectLevel"] = request.ReadIntParameter(result["retOnEffectLevel"]);	
	
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
		result["retStepDelta"] = request.ReadIntParameter(result["retStepDelta"]);	
	
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
		result["retRampRate"] = request.ReadIntParameter(result["retRampRate"]);	
	
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
		result["retIsRamping"] = request.ReadBoolParameter(result["retIsRamping"]);	
	
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
		result["retRampPaused"] = request.ReadBoolParameter(result["retRampPaused"]);	
	
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
		result["retRampTime"] = request.ReadIntParameter(result["retRampTime"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


