 

/**
* Service Proxy for CpProxyAvOpenhomeOrgVolume1
* @module Zapp
* @class Volume
*/
	
var CpProxyAvOpenhomeOrgVolume1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-Volume-1/control";  // upnp control url
	this.domain = "av-openhome-org";
	this.type = "Volume";
	this.version = "1";
	this.serviceName = "av.openhome.org-Volume-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["Volume"] = new Zapp.ServiceProperty("Volume","int");
	this.serviceProperties["Mute"] = new Zapp.ServiceProperty("Mute","bool");
	this.serviceProperties["Balance"] = new Zapp.ServiceProperty("Balance","int");
	this.serviceProperties["Fade"] = new Zapp.ServiceProperty("Fade","int");
	this.serviceProperties["VolumeLimit"] = new Zapp.ServiceProperty("VolumeLimit","int");
	this.serviceProperties["VolumeMax"] = new Zapp.ServiceProperty("VolumeMax","int");
	this.serviceProperties["VolumeUnity"] = new Zapp.ServiceProperty("VolumeUnity","int");
	this.serviceProperties["VolumeSteps"] = new Zapp.ServiceProperty("VolumeSteps","int");
	this.serviceProperties["VolumeMilliDbPerStep"] = new Zapp.ServiceProperty("VolumeMilliDbPerStep","int");
	this.serviceProperties["BalanceMax"] = new Zapp.ServiceProperty("BalanceMax","int");
	this.serviceProperties["FadeMax"] = new Zapp.ServiceProperty("FadeMax","int");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgVolume1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgVolume1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "Volume" property change events
* @method Volume_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Volume_Changed = function (stateChangedFunction) {
    this.serviceProperties.Volume.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Mute" property change events
* @method Mute_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Mute_Changed = function (stateChangedFunction) {
    this.serviceProperties.Mute.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Balance" property change events
* @method Balance_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Balance_Changed = function (stateChangedFunction) {
    this.serviceProperties.Balance.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Fade" property change events
* @method Fade_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Fade_Changed = function (stateChangedFunction) {
    this.serviceProperties.Fade.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "VolumeLimit" property change events
* @method VolumeLimit_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeLimit_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeLimit.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "VolumeMax" property change events
* @method VolumeMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeMax.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "VolumeUnity" property change events
* @method VolumeUnity_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeUnity_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeUnity.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "VolumeSteps" property change events
* @method VolumeSteps_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeSteps_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeSteps.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "VolumeMilliDbPerStep" property change events
* @method VolumeMilliDbPerStep_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeMilliDbPerStep_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeMilliDbPerStep.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "BalanceMax" property change events
* @method BalanceMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.BalanceMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.BalanceMax.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "FadeMax" property change events
* @method FadeMax_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgVolume1.prototype.FadeMax_Changed = function (stateChangedFunction) {
    this.serviceProperties.FadeMax.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to Characteristics
* @method Characteristics
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Characteristics = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Characteristics", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["VolumeMax"] = Zapp.SoapRequest.readIntParameter(result["VolumeMax"]);	
		result["VolumeUnity"] = Zapp.SoapRequest.readIntParameter(result["VolumeUnity"]);	
		result["VolumeSteps"] = Zapp.SoapRequest.readIntParameter(result["VolumeSteps"]);	
		result["VolumeMilliDbPerStep"] = Zapp.SoapRequest.readIntParameter(result["VolumeMilliDbPerStep"]);	
		result["BalanceMax"] = Zapp.SoapRequest.readIntParameter(result["BalanceMax"]);	
		result["FadeMax"] = Zapp.SoapRequest.readIntParameter(result["FadeMax"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetVolume
* @method SetVolume
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.SetVolume = function(Value, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetVolume", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Value", Value);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to VolumeInc
* @method VolumeInc
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeInc = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("VolumeInc", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to VolumeDec
* @method VolumeDec
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeDec = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("VolumeDec", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Volume
* @method Volume
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Volume = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Volume", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readIntParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetBalance
* @method SetBalance
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.SetBalance = function(Value, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetBalance", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Value", Value);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to BalanceInc
* @method BalanceInc
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.BalanceInc = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("BalanceInc", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to BalanceDec
* @method BalanceDec
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.BalanceDec = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("BalanceDec", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Balance
* @method Balance
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Balance = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Balance", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readIntParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetFade
* @method SetFade
* @param {Int} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.SetFade = function(Value, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetFade", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Value", Value);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to FadeInc
* @method FadeInc
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.FadeInc = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("FadeInc", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to FadeDec
* @method FadeDec
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.FadeDec = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("FadeDec", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Fade
* @method Fade
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Fade = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Fade", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readIntParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetMute
* @method SetMute
* @param {Boolean} Value An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.SetMute = function(Value, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetMute", this.url, this.domain, this.type, this.version);		
    request.writeBoolParameter("Value", Value);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Mute
* @method Mute
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.Mute = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Mute", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readBoolParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to VolumeLimit
* @method VolumeLimit
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgVolume1.prototype.VolumeLimit = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("VolumeLimit", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = Zapp.SoapRequest.readIntParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



