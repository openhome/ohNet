 

/**
* Service Proxy for CpProxyLinnCoUkProduct1
* @module Zapp
* @class Product
*/
	
var CpProxyLinnCoUkProduct1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Product-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Product";
	this.version = "1";
	this.serviceName = "linn.co.uk-Product-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["Room"] = new Zapp.ServiceProperty("Room");
	this.serviceProperties["Standby"] = new Zapp.ServiceProperty("Standby");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkProduct1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkProduct1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "Room" property change events
* @method Room_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct1.prototype.Room_Changed = function (stateChangedFunction) {
    this.serviceProperties.Room.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Standby" property change events
* @method Standby_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct1.prototype.Standby_Changed = function (stateChangedFunction) {
    this.serviceProperties.Standby.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* A service action to Room
* @method Room
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct1.prototype.Room = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Room", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aRoom"] = Zapp.SoapRequest.readStringParameter(result["aRoom"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetRoom
* @method SetRoom
* @param {String} aRoom An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct1.prototype.SetRoom = function(aRoom, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetRoom", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("aRoom", aRoom);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Standby
* @method Standby
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct1.prototype.Standby = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Standby", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aStandby"] = Zapp.SoapRequest.readBoolParameter(result["aStandby"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStandby
* @method SetStandby
* @param {Boolean} aStandby An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct1.prototype.SetStandby = function(aStandby, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStandby", this.url, this.formattedDomain, this.type, this.version);		
    request.writeBoolParameter("aStandby", aStandby);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



