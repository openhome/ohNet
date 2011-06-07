 

/**
* Service Proxy for CpProxyAvOpenhomeOrgSender1
* @module ohNet
* @class Sender
*/
	
var CpProxyAvOpenhomeOrgSender1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-Sender-1/control";  // upnp control url
	this.domain = "av-openhome-org";
	this.type = "Sender";
	this.version = "1";
	this.serviceName = "av.openhome.org-Sender-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["PresentationUrl"] = new OhNet.ServiceProperty("PresentationUrl","string");
	this.serviceProperties["Metadata"] = new OhNet.ServiceProperty("Metadata","string");
	this.serviceProperties["Audio"] = new OhNet.ServiceProperty("Audio","bool");
	this.serviceProperties["Status"] = new OhNet.ServiceProperty("Status","string");
	this.serviceProperties["Attributes"] = new OhNet.ServiceProperty("Attributes","string");
}

ServiceSender.kStatusEnabled = "Enabled";
ServiceSender.kStatusDisabled = "Disabled";
ServiceSender.kStatusBlocked = "Blocked";


/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgSender1.prototype.subscribe = function (serviceAddedFunction) {
    OhNet.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgSender1.prototype.unsubscribe = function () {
    OhNet.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "PresentationUrl" property change events
* @method PresentationUrl_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgSender1.prototype.PresentationUrl_Changed = function (stateChangedFunction) {
    this.serviceProperties.PresentationUrl.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Metadata" property change events
* @method Metadata_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgSender1.prototype.Metadata_Changed = function (stateChangedFunction) {
    this.serviceProperties.Metadata.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Audio" property change events
* @method Audio_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgSender1.prototype.Audio_Changed = function (stateChangedFunction) {
    this.serviceProperties.Audio.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readBoolParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Status" property change events
* @method Status_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgSender1.prototype.Status_Changed = function (stateChangedFunction) {
    this.serviceProperties.Status.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "Attributes" property change events
* @method Attributes_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgSender1.prototype.Attributes_Changed = function (stateChangedFunction) {
    this.serviceProperties.Attributes.addListener(function (state) 
	{ 
		stateChangedFunction(OhNet.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to PresentationUrl
* @method PresentationUrl
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgSender1.prototype.PresentationUrl = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("PresentationUrl", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = OhNet.SoapRequest.readStringParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Metadata
* @method Metadata
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgSender1.prototype.Metadata = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("Metadata", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = OhNet.SoapRequest.readStringParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Audio
* @method Audio
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgSender1.prototype.Audio = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("Audio", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = OhNet.SoapRequest.readBoolParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Status
* @method Status
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgSender1.prototype.Status = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("Status", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = OhNet.SoapRequest.readStringParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Attributes
* @method Attributes
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgSender1.prototype.Attributes = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("Attributes", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Value"] = OhNet.SoapRequest.readStringParameter(result["Value"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



