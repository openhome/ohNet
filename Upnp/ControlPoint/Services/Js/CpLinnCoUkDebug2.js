 

/**
* Service Proxy for linn.co.uk:Debug:2
* @module Zapp
* @class Debug
*/

var ServiceDebug = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Debug-2/control";  // upnp control url
	this.domain = "linn.co.uk";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "Debug";
	this.version = "2";
	this.serviceName = "linn.co.uk-Debug-2";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["TUint"] = new Zapp.ServiceProperty("TUint");
	this.serviceProperties["Address"] = new Zapp.ServiceProperty("Address");
	this.serviceProperties["Data"] = new Zapp.ServiceProperty("Data");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceDebug.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServiceDebug.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "TUint" property change events
* @method TUint_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDebug.prototype.TUint_Changed = function (stateChangedFunction) {
    this.serviceProperties.TUint.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Address" property change events
* @method Address_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDebug.prototype.Address_Changed = function (stateChangedFunction) {
    this.serviceProperties.Address.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "Data" property change events
* @method Data_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceDebug.prototype.Data_Changed = function (stateChangedFunction) {
    this.serviceProperties.Data.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBinaryParameter(state)); 
	});
}


/**
* A service action to SetDebugLevel
* @method SetDebugLevel
* @param {Int} aDebugLevel An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceDebug.prototype.SetDebugLevel = function(aDebugLevel, successFunction, errorFunction){	
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
ServiceDebug.prototype.DebugLevel = function(successFunction, errorFunction){	
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
ServiceDebug.prototype.MemWrite = function(aMemAddress, aMemData, successFunction, errorFunction){	
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



