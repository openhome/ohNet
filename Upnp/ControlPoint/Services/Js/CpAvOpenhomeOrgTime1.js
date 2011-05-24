 

/**
* Service Proxy for CpProxyAvOpenhomeOrgTime1
* @module Zapp
* @class Time
*/
	
var CpProxyAvOpenhomeOrgTime1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-Time-1/control";  // upnp control url
	this.domain = "av-openhome-org";
	this.type = "Time";
	this.version = "1";
	this.serviceName = "av.openhome.org-Time-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["TrackCount"] = new Zapp.ServiceProperty("TrackCount","int");
	this.serviceProperties["Duration"] = new Zapp.ServiceProperty("Duration","int");
	this.serviceProperties["Seconds"] = new Zapp.ServiceProperty("Seconds","int");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgTime1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgTime1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "TrackCount" property change events
* @method TrackCount_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgTime1.prototype.TrackCount_Changed = function (stateChangedFunction) {
    this.serviceProperties.TrackCount.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Duration" property change events
* @method Duration_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgTime1.prototype.Duration_Changed = function (stateChangedFunction) {
    this.serviceProperties.Duration.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Seconds" property change events
* @method Seconds_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgTime1.prototype.Seconds_Changed = function (stateChangedFunction) {
    this.serviceProperties.Seconds.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to Time
* @method Time
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgTime1.prototype.Time = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Time", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["TrackCount"] = Zapp.SoapRequest.readIntParameter(result["TrackCount"]);	
		result["Duration"] = Zapp.SoapRequest.readIntParameter(result["Duration"]);	
		result["Seconds"] = Zapp.SoapRequest.readIntParameter(result["Seconds"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



