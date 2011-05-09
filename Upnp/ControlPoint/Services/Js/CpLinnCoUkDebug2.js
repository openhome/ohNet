 

/**
* Service Proxy for CpProxyLinnCoUkDebug2
* @module Zapp
* @class Debug
*/
	
var CpProxyLinnCoUkDebug2 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Debug-2/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Debug";
	this.version = "2";
	this.serviceName = "linn.co.uk-Debug-2";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkDebug2.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkDebug2.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* A service action to SetDebugLevel
* @method SetDebugLevel
* @param {Int} aDebugLevel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDebug2.prototype.SetDebugLevel = function(aDebugLevel, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetDebugLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aDebugLevel", aDebugLevel);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to DebugLevel
* @method DebugLevel
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDebug2.prototype.DebugLevel = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("DebugLevel", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aDebugLevel"] = Zapp.SoapRequest.readIntParameter(result["aDebugLevel"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to MemWrite
* @method MemWrite
* @param {Int} aMemAddress An action parameter
* @param {String} aMemData An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkDebug2.prototype.MemWrite = function(aMemAddress, aMemData, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("MemWrite", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aMemAddress", aMemAddress);
    request.writeBinaryParameter("aMemData", aMemData);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



