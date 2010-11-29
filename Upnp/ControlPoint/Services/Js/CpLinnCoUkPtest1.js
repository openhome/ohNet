 

/**
* Service Proxy for linn.co.uk:Ptest:1
* @module Zapp
* @class Ptest
*/

var ServicePtest = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Ptest-1/control";  // upnp control url
	this.domain = "linn.co.uk";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "Ptest";
	this.version = "1";
	this.serviceName = "linn.co.uk-Ptest-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["Bool"] = new Zapp.ServiceProperty("Bool");
	this.serviceProperties["ComPort"] = new Zapp.ServiceProperty("ComPort");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServicePtest.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServicePtest.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "Bool" property change events
* @method Bool_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePtest.prototype.Bool_Changed = function (stateChangedFunction) {
    this.serviceProperties.Bool.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* Adds a listener to handle "ComPort" property change events
* @method ComPort_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServicePtest.prototype.ComPort_Changed = function (stateChangedFunction) {
    this.serviceProperties.ComPort.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to TestComPort
* @method TestComPort
* @param {Int} aPort An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePtest.prototype.TestComPort = function(aPort, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("TestComPort", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aPort", aPort);
    request.send(function(result){
		result["aResult"] = Zapp.SoapRequest.readBoolParameter(result["aResult"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to LedsOn
* @method LedsOn
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePtest.prototype.LedsOn = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("LedsOn", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to LedsOff
* @method LedsOff
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServicePtest.prototype.LedsOff = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("LedsOff", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



