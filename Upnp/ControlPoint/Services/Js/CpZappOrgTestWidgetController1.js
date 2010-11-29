 

/**
* Service Proxy for zapp.org:TestWidgetController:1
* @module Zapp
* @class TestWidgetController
*/

var ServiceTestWidgetController = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/zapp.org-TestWidgetController-1/control";  // upnp control url
	this.domain = "zapp.org";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "TestWidgetController";
	this.version = "1";
	this.serviceName = "zapp.org-TestWidgetController-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["RegisterValue"] = new Zapp.ServiceProperty("RegisterValue");
	this.serviceProperties["RegisterIndex"] = new Zapp.ServiceProperty("RegisterIndex");
	this.serviceProperties["UDN"] = new Zapp.ServiceProperty("UDN");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceTestWidgetController.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServiceTestWidgetController.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "RegisterValue" property change events
* @method RegisterValue_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidgetController.prototype.RegisterValue_Changed = function (stateChangedFunction) {
    this.serviceProperties.RegisterValue.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "RegisterIndex" property change events
* @method RegisterIndex_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidgetController.prototype.RegisterIndex_Changed = function (stateChangedFunction) {
    this.serviceProperties.RegisterIndex.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "UDN" property change events
* @method UDN_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidgetController.prototype.UDN_Changed = function (stateChangedFunction) {
    this.serviceProperties.UDN.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to CreateWidget
* @method CreateWidget
* @param {String} WidgetUdn An action parameter
* @param {Int} WidgetClass An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestWidgetController.prototype.CreateWidget = function(WidgetUdn, WidgetClass, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("CreateWidget", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("WidgetUdn", WidgetUdn);
    request.writeIntParameter("WidgetClass", WidgetClass);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to RemoveWidget
* @method RemoveWidget
* @param {String} WidgetUdn An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestWidgetController.prototype.RemoveWidget = function(WidgetUdn, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("RemoveWidget", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("WidgetUdn", WidgetUdn);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetWidgetRegister
* @method SetWidgetRegister
* @param {String} WidgetUdn An action parameter
* @param {Int} RegisterIndex An action parameter
* @param {Int} RegisterValue An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestWidgetController.prototype.SetWidgetRegister = function(WidgetUdn, RegisterIndex, RegisterValue, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetWidgetRegister", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("WidgetUdn", WidgetUdn);
    request.writeIntParameter("RegisterIndex", RegisterIndex);
    request.writeIntParameter("RegisterValue", RegisterValue);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetWidgetRegister
* @method GetWidgetRegister
* @param {String} WidgetUdn An action parameter
* @param {Int} RegisterIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestWidgetController.prototype.GetWidgetRegister = function(WidgetUdn, RegisterIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetWidgetRegister", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("WidgetUdn", WidgetUdn);
    request.writeIntParameter("RegisterIndex", RegisterIndex);
    request.send(function(result){
		result["RegisterValue"] = Zapp.SoapRequest.readIntParameter(result["RegisterValue"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



