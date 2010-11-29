 

/**
* Service Proxy for upnp.org:Dimming:1
* @module Zapp
* @class Dimming
*/

var ServiceDimming = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-Dimming-1/control";  // upnp control url
	this.domain = "upnp.org";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "Dimming";
	this.version = "1";
	this.serviceName = "upnp.org-Dimming-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["LoadLevelTarget"] = new Zapp.ServiceProperty("LoadLevelTarget");
	this.serviceProperties["LoadLevelStatus"] = new Zapp.ServiceProperty("LoadLevelStatus");
	this.serviceProperties["MinLevel"] = new Zapp.ServiceProperty("MinLevel");
	this.serviceProperties["OnEffectLevel"] = new Zapp.ServiceProperty("OnEffectLevel");
	this.serviceProperties["OnEffect"] = new Zapp.ServiceProperty("OnEffect");
	this.serviceProperties["ValidOutputValues"] = new Zapp.ServiceProperty("ValidOutputValues");
	this.serviceProperties["StepDelta"] = new Zapp.ServiceProperty("StepDelta");
	this.serviceProperties["RampRate"] = new Zapp.ServiceProperty("RampRate");
	this.serviceProperties["RampTime"] = new Zapp.ServiceProperty("RampTime");
	this.serviceProperties["IsRamping"] = new Zapp.ServiceProperty("IsRamping");
	this.serviceProperties["RampPaused"] = new Zapp.ServiceProperty("RampPaused");
}

ServiceDimming.kOnEffectOnEffectLevel = "OnEffectLevel";
ServiceDimming.kOnEffectLastSetting = "LastSetting";
ServiceDimming.kOnEffectDefault = "Default";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceDimming.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServiceDimming.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "LoadLevelTarget" property change events
* @method LoadLevelTarget_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.LoadLevelTarget_Changed = function (stateChangedFunction) {
    this.serviceProperties.LoadLevelTarget.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "LoadLevelStatus" property change events
* @method LoadLevelStatus_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.LoadLevelStatus_Changed = function (stateChangedFunction) {
    this.serviceProperties.LoadLevelStatus.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "MinLevel" property change events
* @method MinLevel_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.MinLevel_Changed = function (stateChangedFunction) {
    this.serviceProperties.MinLevel.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "OnEffectLevel" property change events
* @method OnEffectLevel_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.OnEffectLevel_Changed = function (stateChangedFunction) {
    this.serviceProperties.OnEffectLevel.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "OnEffect" property change events
* @method OnEffect_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.OnEffect_Changed = function (stateChangedFunction) {
    this.serviceProperties.OnEffect.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ValidOutputValues" property change events
* @method ValidOutputValues_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.ValidOutputValues_Changed = function (stateChangedFunction) {
    this.serviceProperties.ValidOutputValues.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "StepDelta" property change events
* @method StepDelta_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.StepDelta_Changed = function (stateChangedFunction) {
    this.serviceProperties.StepDelta.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "RampRate" property change events
* @method RampRate_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.RampRate_Changed = function (stateChangedFunction) {
    this.serviceProperties.RampRate.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "RampTime" property change events
* @method RampTime_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.RampTime_Changed = function (stateChangedFunction) {
    this.serviceProperties.RampTime.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "IsRamping" property change events
* @method IsRamping_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.IsRamping_Changed = function (stateChangedFunction) {
    this.serviceProperties.IsRamping.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "RampPaused" property change events
* @method RampPaused_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDimming.prototype.RampPaused_Changed = function (stateChangedFunction) {
    this.serviceProperties.RampPaused.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* A service action to SetLoadLevelTarget
* @method SetLoadLevelTarget
* @param {Int} newLoadlevelTarget An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.SetLoadLevelTarget = function(newLoadlevelTarget, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetLoadLevelTarget", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("newLoadlevelTarget", newLoadlevelTarget);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetLoadLevelTarget
* @method GetLoadLevelTarget
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.GetLoadLevelTarget = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetLoadLevelTarget", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["GetLoadlevelTarget"] = Zapp.SoapRequest.readIntParameter(result["GetLoadlevelTarget"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetLoadLevelStatus
* @method GetLoadLevelStatus
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.GetLoadLevelStatus = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetLoadLevelStatus", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["retLoadlevelStatus"] = Zapp.SoapRequest.readIntParameter(result["retLoadlevelStatus"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetOnEffectLevel
* @method SetOnEffectLevel
* @param {Int} newOnEffectLevel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.SetOnEffectLevel = function(newOnEffectLevel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetOnEffectLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("newOnEffectLevel", newOnEffectLevel);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetOnEffect
* @method SetOnEffect
* @param {String} newOnEffect An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.SetOnEffect = function(newOnEffect, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetOnEffect", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("newOnEffect", newOnEffect);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetOnEffectParameters
* @method GetOnEffectParameters
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.GetOnEffectParameters = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetOnEffectParameters", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["retOnEffect"] = Zapp.SoapRequest.readStringParameter(result["retOnEffect"]);	
		result["retOnEffectLevel"] = Zapp.SoapRequest.readIntParameter(result["retOnEffectLevel"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StepUp
* @method StepUp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.StepUp = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StepUp", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StepDown
* @method StepDown
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.StepDown = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StepDown", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StartRampUp
* @method StartRampUp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.StartRampUp = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StartRampUp", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StartRampDown
* @method StartRampDown
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.StartRampDown = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StartRampDown", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StopRamp
* @method StopRamp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.StopRamp = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StopRamp", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StartRampToLevel
* @method StartRampToLevel
* @param {Int} newLoadLevelTarget An action parameter
* @param {Int} newRampTime An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.StartRampToLevel = function(newLoadLevelTarget, newRampTime, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StartRampToLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("newLoadLevelTarget", newLoadLevelTarget);
    request.writeIntParameter("newRampTime", newRampTime);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStepDelta
* @method SetStepDelta
* @param {Int} newStepDelta An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.SetStepDelta = function(newStepDelta, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStepDelta", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("newStepDelta", newStepDelta);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetStepDelta
* @method GetStepDelta
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.GetStepDelta = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetStepDelta", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["retStepDelta"] = Zapp.SoapRequest.readIntParameter(result["retStepDelta"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetRampRate
* @method SetRampRate
* @param {Int} newRampRate An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.SetRampRate = function(newRampRate, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetRampRate", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("newRampRate", newRampRate);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetRampRate
* @method GetRampRate
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.GetRampRate = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRampRate", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["retRampRate"] = Zapp.SoapRequest.readIntParameter(result["retRampRate"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PauseRamp
* @method PauseRamp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.PauseRamp = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("PauseRamp", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ResumeRamp
* @method ResumeRamp
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.ResumeRamp = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ResumeRamp", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetIsRamping
* @method GetIsRamping
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.GetIsRamping = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetIsRamping", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["retIsRamping"] = Zapp.SoapRequest.readBoolParameter(result["retIsRamping"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetRampPaused
* @method GetRampPaused
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.GetRampPaused = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRampPaused", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["retRampPaused"] = Zapp.SoapRequest.readBoolParameter(result["retRampPaused"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetRampTime
* @method GetRampTime
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDimming.prototype.GetRampTime = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRampTime", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["retRampTime"] = Zapp.SoapRequest.readIntParameter(result["retRampTime"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



