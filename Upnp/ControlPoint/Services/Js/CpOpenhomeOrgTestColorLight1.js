 

/**
* Service Proxy for openhome.org:TestColorLight:1
* @module Zapp
* @class TestColorLight
*/

var ServiceTestColorLight = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/openhome.org-TestColorLight-1/control";  // upnp control url
	this.domain = "openhome.org";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "TestColorLight";
	this.version = "1";
	this.serviceName = "openhome.org-TestColorLight-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["A_ARG_GetName_FriendlyName"] = new Zapp.ServiceProperty("A_ARG_GetName_FriendlyName");
	this.serviceProperties["A_ARG_Color_Red"] = new Zapp.ServiceProperty("A_ARG_Color_Red");
	this.serviceProperties["A_ARG_Color_Green"] = new Zapp.ServiceProperty("A_ARG_Color_Green");
	this.serviceProperties["A_ARG_Color_Blue"] = new Zapp.ServiceProperty("A_ARG_Color_Blue");
	this.serviceProperties["A_ARG_ColorBits_Red"] = new Zapp.ServiceProperty("A_ARG_ColorBits_Red");
	this.serviceProperties["A_ARG_ColorBits_Green"] = new Zapp.ServiceProperty("A_ARG_ColorBits_Green");
	this.serviceProperties["A_ARG_ColorBits_Blue"] = new Zapp.ServiceProperty("A_ARG_ColorBits_Blue");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceTestColorLight.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServiceTestColorLight.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "A_ARG_GetName_FriendlyName" property change events
* @method A_ARG_GetName_FriendlyName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestColorLight.prototype.A_ARG_GetName_FriendlyName_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetName_FriendlyName.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_Color_Red" property change events
* @method A_ARG_Color_Red_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestColorLight.prototype.A_ARG_Color_Red_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_Color_Red.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_Color_Green" property change events
* @method A_ARG_Color_Green_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestColorLight.prototype.A_ARG_Color_Green_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_Color_Green.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_Color_Blue" property change events
* @method A_ARG_Color_Blue_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestColorLight.prototype.A_ARG_Color_Blue_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_Color_Blue.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_ColorBits_Red" property change events
* @method A_ARG_ColorBits_Red_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestColorLight.prototype.A_ARG_ColorBits_Red_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_ColorBits_Red.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_ColorBits_Green" property change events
* @method A_ARG_ColorBits_Green_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestColorLight.prototype.A_ARG_ColorBits_Green_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_ColorBits_Green.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_ColorBits_Blue" property change events
* @method A_ARG_ColorBits_Blue_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestColorLight.prototype.A_ARG_ColorBits_Blue_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_ColorBits_Blue.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to GetName
* @method GetName
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestColorLight.prototype.GetName = function(successFunction, errorFunction){	
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
ServiceTestColorLight.prototype.SetColor = function(Red, Green, Blue, successFunction, errorFunction){	
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
ServiceTestColorLight.prototype.GetColor = function(successFunction, errorFunction){	
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
ServiceTestColorLight.prototype.GetMaxColors = function(successFunction, errorFunction){	
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



