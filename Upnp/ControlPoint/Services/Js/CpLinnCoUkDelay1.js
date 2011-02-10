 

/**
* Service Proxy for linn-co-uk:Delay:1
* @module Zapp
* @class Delay
*/
	
var CpProxyLinnCoUkDelay1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn-co-uk-Delay-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Delay";
	this.version = "1";
	this.serviceName = "CpProxyLinnCoUkDelay1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["PresetXml"] = new Zapp.ServiceProperty("PresetXml");
	this.serviceProperties["PresetIndex"] = new Zapp.ServiceProperty("PresetIndex");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkDelay1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkDelay1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "PresetXml" property change events
* @method PresetXml_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDelay1.prototype.PresetXml_Changed = function (stateChangedFunction) {
    this.serviceProperties.PresetXml.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "PresetIndex" property change events
* @method PresetIndex_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkDelay1.prototype.PresetIndex_Changed = function (stateChangedFunction) {
    this.serviceProperties.PresetIndex.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to PresetXml
* @method PresetXml
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDelay1.prototype.PresetXml = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("PresetXml", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aPresetXml"] = Zapp.SoapRequest.readStringParameter(result["aPresetXml"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PresetIndex
* @method PresetIndex
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDelay1.prototype.PresetIndex = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("PresetIndex", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aIndex"] = Zapp.SoapRequest.readIntParameter(result["aIndex"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetPresetIndex
* @method SetPresetIndex
* @param {Int} aIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDelay1.prototype.SetPresetIndex = function(aIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetPresetIndex", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aIndex", aIndex);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetPresetDelay
* @method SetPresetDelay
* @param {Int} aIndex An action parameter
* @param {Int} aDelay An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDelay1.prototype.SetPresetDelay = function(aIndex, aDelay, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetPresetDelay", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aIndex", aIndex);
    request.writeIntParameter("aDelay", aDelay);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetPresetVisible
* @method SetPresetVisible
* @param {Int} aIndex An action parameter
* @param {Boolean} aVisible An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDelay1.prototype.SetPresetVisible = function(aIndex, aVisible, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetPresetVisible", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aIndex", aIndex);
    request.writeBoolParameter("aVisible", aVisible);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetPresetName
* @method SetPresetName
* @param {Int} aIndex An action parameter
* @param {String} aName An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDelay1.prototype.SetPresetName = function(aIndex, aName, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetPresetName", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aIndex", aIndex);
    request.writeStringParameter("aName", aName);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DelayMinimum
* @method DelayMinimum
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDelay1.prototype.DelayMinimum = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DelayMinimum", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aDelay"] = Zapp.SoapRequest.readIntParameter(result["aDelay"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DelayMaximum
* @method DelayMaximum
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDelay1.prototype.DelayMaximum = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DelayMaximum", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aDelay"] = Zapp.SoapRequest.readIntParameter(result["aDelay"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to PresetCount
* @method PresetCount
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDelay1.prototype.PresetCount = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("PresetCount", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aCount"] = Zapp.SoapRequest.readIntParameter(result["aCount"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



