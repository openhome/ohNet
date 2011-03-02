 

/**
* Service Proxy for CpProxySchemasUpnpOrgSwitchPower1
* @module Zapp
* @class SwitchPower
*/
	
var CpProxySchemasUpnpOrgSwitchPower1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/upnp.org-SwitchPower-1/control";  // upnp control url
	this.domain = "schemas-upnp-org";
	this.type = "SwitchPower";
	this.version = "1";
	this.serviceName = "upnp.org-SwitchPower-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["Status"] = new Zapp.ServiceProperty("Status");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxySchemasUpnpOrgSwitchPower1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxySchemasUpnpOrgSwitchPower1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "Status" property change events
* @method Status_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxySchemasUpnpOrgSwitchPower1.prototype.Status_Changed = function (stateChangedFunction) {
    this.serviceProperties.Status.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}


/**
* A service action to SetTarget
* @method SetTarget
* @param {Boolean} newTargetValue An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgSwitchPower1.prototype.SetTarget = function(newTargetValue, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetTarget", this.url, this.formattedDomain, this.type, this.version);		
    request.writeBoolParameter("newTargetValue", newTargetValue);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetTarget
* @method GetTarget
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgSwitchPower1.prototype.GetTarget = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetTarget", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["RetTargetValue"] = Zapp.SoapRequest.readBoolParameter(result["RetTargetValue"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetStatus
* @method GetStatus
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxySchemasUpnpOrgSwitchPower1.prototype.GetStatus = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetStatus", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["ResultStatus"] = Zapp.SoapRequest.readBoolParameter(result["ResultStatus"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



