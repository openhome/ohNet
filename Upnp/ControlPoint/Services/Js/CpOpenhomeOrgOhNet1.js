 

/**
* Service Proxy for CpProxyOpenhomeOrgOhNet1
* @module Zapp
* @class OhNet
*/
	
var CpProxyOpenhomeOrgOhNet1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/openhome.org-OhNet-1/control";  // upnp control url
	this.domain = "openhome-org";
	this.type = "OhNet";
	this.version = "1";
	this.serviceName = "openhome.org-OhNet-1";
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
CpProxyOpenhomeOrgOhNet1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyOpenhomeOrgOhNet1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* A service action to GetWebSocketPort
* @method GetWebSocketPort
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgOhNet1.prototype.GetWebSocketPort = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetWebSocketPort", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Port"] = Zapp.SoapRequest.readIntParameter(result["Port"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



