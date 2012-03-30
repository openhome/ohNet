 

/**
* Service Proxy for CpProxyOpenhomeOrgSubscriptionLongPoll1
* @module ohnet
* @class SubscriptionLongPoll
*/
	
var CpProxyOpenhomeOrgSubscriptionLongPoll1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/openhome.org-SubscriptionLongPoll-1/control";  // upnp control url
	this.domain = "openhome-org";
	this.type = "SubscriptionLongPoll";
	this.version = "1";
	this.serviceName = "openhome.org-SubscriptionLongPoll-1";
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
CpProxyOpenhomeOrgSubscriptionLongPoll1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyOpenhomeOrgSubscriptionLongPoll1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}




/**
* A service action to Subscribe
* @method Subscribe
* @param {String} ClientId An action parameter
* @param {String} Udn An action parameter
* @param {String} Service An action parameter
* @param {Int} RequestedDuration An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgSubscriptionLongPoll1.prototype.Subscribe = function(ClientId, Udn, Service, RequestedDuration, successFunction, errorFunction){	
	var request = new ohnet.soaprequest("Subscribe", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("ClientId", ClientId);
    request.writeStringParameter("Udn", Udn);
    request.writeStringParameter("Service", Service);
    request.writeIntParameter("RequestedDuration", RequestedDuration);
    request.send(function(result){
		result["Sid"] = ohnet.soaprequest.readStringParameter(result["Sid"]);	
		result["Duration"] = ohnet.soaprequest.readIntParameter(result["Duration"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Unsubscribe
* @method Unsubscribe
* @param {String} Sid An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgSubscriptionLongPoll1.prototype.Unsubscribe = function(Sid, successFunction, errorFunction){	
	var request = new ohnet.soaprequest("Unsubscribe", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("Sid", Sid);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Renew
* @method Renew
* @param {String} Sid An action parameter
* @param {Int} RequestedDuration An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgSubscriptionLongPoll1.prototype.Renew = function(Sid, RequestedDuration, successFunction, errorFunction){	
	var request = new ohnet.soaprequest("Renew", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("Sid", Sid);
    request.writeIntParameter("RequestedDuration", RequestedDuration);
    request.send(function(result){
		result["Duration"] = ohnet.soaprequest.readIntParameter(result["Duration"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetPropertyUpdates
* @method GetPropertyUpdates
* @param {String} ClientId An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgSubscriptionLongPoll1.prototype.GetPropertyUpdates = function(ClientId, successFunction, errorFunction){	
	var request = new ohnet.soaprequest("GetPropertyUpdates", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("ClientId", ClientId);
    request.send(function(result){
		result["Updates"] = ohnet.soaprequest.readStringParameter(result["Updates"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



