 

/**
* Service Proxy for CpProxyLinnCoUkConfiguration1
* @module Zapp
* @class Configuration
*/
	
var CpProxyLinnCoUkConfiguration1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Configuration-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Configuration";
	this.version = "1";
	this.serviceName = "linn.co.uk-Configuration-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["ConfigurationXml"] = new Zapp.ServiceProperty("ConfigurationXml");
	this.serviceProperties["ParameterXml"] = new Zapp.ServiceProperty("ParameterXml");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkConfiguration1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkConfiguration1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "ConfigurationXml" property change events
* @method ConfigurationXml_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkConfiguration1.prototype.ConfigurationXml_Changed = function (stateChangedFunction) {
    this.serviceProperties.ConfigurationXml.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ParameterXml" property change events
* @method ParameterXml_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkConfiguration1.prototype.ParameterXml_Changed = function (stateChangedFunction) {
    this.serviceProperties.ParameterXml.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to ConfigurationXml
* @method ConfigurationXml
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkConfiguration1.prototype.ConfigurationXml = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ConfigurationXml", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aConfigurationXml"] = Zapp.SoapRequest.readStringParameter(result["aConfigurationXml"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ParameterXml
* @method ParameterXml
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkConfiguration1.prototype.ParameterXml = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ParameterXml", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aParameterXml"] = Zapp.SoapRequest.readStringParameter(result["aParameterXml"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetParameter
* @method SetParameter
* @param {String} aTarget An action parameter
* @param {String} aName An action parameter
* @param {String} aValue An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkConfiguration1.prototype.SetParameter = function(aTarget, aName, aValue, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetParameter", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("aTarget", aTarget);
    request.writeStringParameter("aName", aName);
    request.writeStringParameter("aValue", aValue);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



