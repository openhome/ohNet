 

/**
* Service Proxy for CpProxyLinnCoUkMediaTime1
* @module Zapp
* @class MediaTime
*/
	
var CpProxyLinnCoUkMediaTime1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-MediaTime-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "MediaTime";
	this.version = "1";
	this.serviceName = "linn.co.uk-MediaTime-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["Seconds"] = new Zapp.ServiceProperty("Seconds","int");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkMediaTime1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkMediaTime1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "Seconds" property change events
* @method Seconds_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkMediaTime1.prototype.Seconds_Changed = function (stateChangedFunction) {
    this.serviceProperties.Seconds.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to Seconds
* @method Seconds
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkMediaTime1.prototype.Seconds = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Seconds", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aSeconds"] = Zapp.SoapRequest.readIntParameter(result["aSeconds"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



