 

/**
* Service Proxy for CpProxyZappOrgTestDimmableLight1
* @module Zapp
* @class TestDimmableLight
*/
	
var CpProxyZappOrgTestDimmableLight1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/zapp.org-TestDimmableLight-1/control";  // upnp control url
	this.domain = "zapp-org";
	this.type = "TestDimmableLight";
	this.version = "1";
	this.serviceName = "zapp.org-TestDimmableLight-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["A_ARG_Level"] = new Zapp.ServiceProperty("A_ARG_Level");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyZappOrgTestDimmableLight1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyZappOrgTestDimmableLight1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "A_ARG_Level" property change events
* @method A_ARG_Level_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyZappOrgTestDimmableLight1.prototype.A_ARG_Level_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_Level.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to GetLevel
* @method GetLevel
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyZappOrgTestDimmableLight1.prototype.GetLevel = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetLevel", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["Level"] = Zapp.SoapRequest.readIntParameter(result["Level"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetLevel
* @method SetLevel
* @param {Int} Level An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyZappOrgTestDimmableLight1.prototype.SetLevel = function(Level, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetLevel", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("Level", Level);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



