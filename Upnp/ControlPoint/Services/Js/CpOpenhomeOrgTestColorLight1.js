 

/**
* Service Proxy for CpProxyOpenhomeOrgTestColorLight1
* @module Zapp
* @class TestColorLight
*/
	
var CpProxyOpenhomeOrgTestColorLight1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/openhome.org-TestColorLight-1/control";  // upnp control url
	this.domain = "openhome-org";
	this.type = "TestColorLight";
	this.version = "1";
	this.serviceName = "openhome.org-TestColorLight-1";
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
CpProxyOpenhomeOrgTestColorLight1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyOpenhomeOrgTestColorLight1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* A service action to GetName
* @method GetName
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestColorLight1.prototype.GetName = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetName", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["FriendlyName"] = Zapp.SoapRequest.readStringParameter(result["FriendlyName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetColor
* @method SetColor
* @param {Int} Red An action parameter
* @param {Int} Green An action parameter
* @param {Int} Blue An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestColorLight1.prototype.SetColor = function(Red, Green, Blue, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetColor", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Red", Red);
    request.writeIntParameter("Green", Green);
    request.writeIntParameter("Blue", Blue);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetColor
* @method GetColor
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestColorLight1.prototype.GetColor = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetColor", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Red"] = Zapp.SoapRequest.readIntParameter(result["Red"]);	
		result["Green"] = Zapp.SoapRequest.readIntParameter(result["Green"]);	
		result["Blue"] = Zapp.SoapRequest.readIntParameter(result["Blue"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetMaxColors
* @method GetMaxColors
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestColorLight1.prototype.GetMaxColors = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetMaxColors", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Red"] = Zapp.SoapRequest.readIntParameter(result["Red"]);	
		result["Green"] = Zapp.SoapRequest.readIntParameter(result["Green"]);	
		result["Blue"] = Zapp.SoapRequest.readIntParameter(result["Blue"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



