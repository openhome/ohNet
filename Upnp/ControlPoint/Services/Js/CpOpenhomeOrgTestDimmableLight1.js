 

/**
* Service Proxy for CpProxyOpenhomeOrgTestDimmableLight1
* @module ohNet
* @class TestDimmableLight
*/
	
var CpProxyOpenhomeOrgTestDimmableLight1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/openhome.org-TestDimmableLight-1/control";  // upnp control url
	this.domain = "openhome-org";
	this.type = "TestDimmableLight";
	this.version = "1";
	this.serviceName = "openhome.org-TestDimmableLight-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["A_ARG_Level"] = new OhNet.ServiceProperty("A_ARG_Level","int");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyOpenhomeOrgTestDimmableLight1.prototype.subscribe = function (serviceAddedFunction) {
    OhNet.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyOpenhomeOrgTestDimmableLight1.prototype.unsubscribe = function () {
    OhNet.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "A_ARG_Level" property change events
* @method A_ARG_Level_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyOpenhomeOrgTestDimmableLight1.prototype.A_ARG_Level_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_Level.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to GetLevel
* @method GetLevel
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestDimmableLight1.prototype.GetLevel = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetLevel", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Level"] = OhNet.SoapRequest.readIntParameter(result["Level"]);	
	
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
CpProxyOpenhomeOrgTestDimmableLight1.prototype.SetLevel = function(Level, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("SetLevel", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Level", Level);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



