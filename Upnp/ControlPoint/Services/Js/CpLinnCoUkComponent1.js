 

/**
* Service Proxy for CpProxyLinnCoUkComponent1
* @module Zapp
* @class Component
*/
	
var CpProxyLinnCoUkComponent1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Component-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Component";
	this.version = "1";
	this.serviceName = "linn.co.uk-Component-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["AmplifierEnabled"] = new Zapp.ServiceProperty("AmplifierEnabled");
	this.serviceProperties["AmplifierAttenuation"] = new Zapp.ServiceProperty("AmplifierAttenuation");
	this.serviceProperties["VolumeControlEnabled"] = new Zapp.ServiceProperty("VolumeControlEnabled");
	this.serviceProperties["DigitalAudioOutputRaw"] = new Zapp.ServiceProperty("DigitalAudioOutputRaw");
}

ServiceComponent.kAmplifierAttenuation12Db = "-12dB";
ServiceComponent.kAmplifierAttenuation9Db = "-9dB";
ServiceComponent.kAmplifierAttenuation6Db = "-6dB";
ServiceComponent.kAmplifierAttenuation0Db = "0dB";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkComponent1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkComponent1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "AmplifierEnabled" property change events
* @method AmplifierEnabled_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkComponent1.prototype.AmplifierEnabled_Changed = function (stateChangedFunction) {
    this.serviceProperties.AmplifierEnabled.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "AmplifierAttenuation" property change events
* @method AmplifierAttenuation_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkComponent1.prototype.AmplifierAttenuation_Changed = function (stateChangedFunction) {
    this.serviceProperties.AmplifierAttenuation.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "VolumeControlEnabled" property change events
* @method VolumeControlEnabled_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkComponent1.prototype.VolumeControlEnabled_Changed = function (stateChangedFunction) {
    this.serviceProperties.VolumeControlEnabled.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "DigitalAudioOutputRaw" property change events
* @method DigitalAudioOutputRaw_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkComponent1.prototype.DigitalAudioOutputRaw_Changed = function (stateChangedFunction) {
    this.serviceProperties.DigitalAudioOutputRaw.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* A service action to AmplifierEnabled
* @method AmplifierEnabled
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.AmplifierEnabled = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("AmplifierEnabled", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aEnabled"] = Zapp.SoapRequest.readBoolParameter(result["aEnabled"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetAmplifierEnabled
* @method SetAmplifierEnabled
* @param {Boolean} aEnabled An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.SetAmplifierEnabled = function(aEnabled, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetAmplifierEnabled", this.url, this.formattedDomain, this.type, this.version);		
    request.writeBoolParameter("aEnabled", aEnabled);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to AmplifierAttenuation
* @method AmplifierAttenuation
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.AmplifierAttenuation = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("AmplifierAttenuation", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aAttenuation"] = Zapp.SoapRequest.readStringParameter(result["aAttenuation"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetAmplifierAttenuation
* @method SetAmplifierAttenuation
* @param {String} aAttenuation An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.SetAmplifierAttenuation = function(aAttenuation, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetAmplifierAttenuation", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("aAttenuation", aAttenuation);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetVolumeControlEnabled
* @method SetVolumeControlEnabled
* @param {Boolean} aEnabled An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.SetVolumeControlEnabled = function(aEnabled, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetVolumeControlEnabled", this.url, this.formattedDomain, this.type, this.version);		
    request.writeBoolParameter("aEnabled", aEnabled);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to VolumeControlEnabled
* @method VolumeControlEnabled
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.VolumeControlEnabled = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("VolumeControlEnabled", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aEnabled"] = Zapp.SoapRequest.readBoolParameter(result["aEnabled"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetDigitalAudioOutputRaw
* @method SetDigitalAudioOutputRaw
* @param {Boolean} aRaw An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.SetDigitalAudioOutputRaw = function(aRaw, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetDigitalAudioOutputRaw", this.url, this.formattedDomain, this.type, this.version);		
    request.writeBoolParameter("aRaw", aRaw);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DigitalAudioOutputRaw
* @method DigitalAudioOutputRaw
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.DigitalAudioOutputRaw = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DigitalAudioOutputRaw", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aRaw"] = Zapp.SoapRequest.readBoolParameter(result["aRaw"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to AmplifierOverTemperature
* @method AmplifierOverTemperature
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.AmplifierOverTemperature = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("AmplifierOverTemperature", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aOverTemperature"] = Zapp.SoapRequest.readBoolParameter(result["aOverTemperature"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to EthernetLinkConnected
* @method EthernetLinkConnected
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.EthernetLinkConnected = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("EthernetLinkConnected", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aLinkConnected"] = Zapp.SoapRequest.readBoolParameter(result["aLinkConnected"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Locate
* @method Locate
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkComponent1.prototype.Locate = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Locate", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



