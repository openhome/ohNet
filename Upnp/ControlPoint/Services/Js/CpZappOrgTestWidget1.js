 

/**
* Service Proxy for zapp.org:TestWidget:1
* @module Zapp
* @title TestWidget
*/

var ServiceTestWidget = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/zapp.org-TestWidget-1/control";  // upnp control url
	this.domain = "zapp.org";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "TestWidget";
	this.version = "1";
	this.serviceName = "zapp.org-TestWidget-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["RegisterValue"] = new Zapp.ServiceProperty("RegisterValue");
	this.serviceProperties["RegisterIndex"] = new Zapp.ServiceProperty("RegisterIndex");
	this.serviceProperties["WidgetClass"] = new Zapp.ServiceProperty("WidgetClass");
	this.serviceProperties["ReadWriteRegister0"] = new Zapp.ServiceProperty("ReadWriteRegister0");
	this.serviceProperties["ReadWriteRegister1"] = new Zapp.ServiceProperty("ReadWriteRegister1");
	this.serviceProperties["ReadWriteRegister2"] = new Zapp.ServiceProperty("ReadWriteRegister2");
	this.serviceProperties["ReadWriteRegister3"] = new Zapp.ServiceProperty("ReadWriteRegister3");
	this.serviceProperties["ReadOnlyRegister4"] = new Zapp.ServiceProperty("ReadOnlyRegister4");
	this.serviceProperties["ReadOnlyRegister5"] = new Zapp.ServiceProperty("ReadOnlyRegister5");
	this.serviceProperties["ReadOnlyRegister6"] = new Zapp.ServiceProperty("ReadOnlyRegister6");
	this.serviceProperties["ReadOnlyRegister7"] = new Zapp.ServiceProperty("ReadOnlyRegister7");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceTestWidget.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Subscribed
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceTestWidget.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "RegisterValue" property change events
* @method RegisterValue_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.RegisterValue_Changed = function (stateChangedFunction) {
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
ServiceTestWidget.prototype.RegisterIndex_Changed = function (stateChangedFunction) {
    this.serviceProperties.RegisterIndex.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "WidgetClass" property change events
* @method WidgetClass_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.WidgetClass_Changed = function (stateChangedFunction) {
    this.serviceProperties.WidgetClass.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ReadWriteRegister0" property change events
* @method ReadWriteRegister0_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.ReadWriteRegister0_Changed = function (stateChangedFunction) {
    this.serviceProperties.ReadWriteRegister0.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ReadWriteRegister1" property change events
* @method ReadWriteRegister1_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.ReadWriteRegister1_Changed = function (stateChangedFunction) {
    this.serviceProperties.ReadWriteRegister1.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ReadWriteRegister2" property change events
* @method ReadWriteRegister2_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.ReadWriteRegister2_Changed = function (stateChangedFunction) {
    this.serviceProperties.ReadWriteRegister2.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ReadWriteRegister3" property change events
* @method ReadWriteRegister3_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.ReadWriteRegister3_Changed = function (stateChangedFunction) {
    this.serviceProperties.ReadWriteRegister3.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ReadOnlyRegister4" property change events
* @method ReadOnlyRegister4_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.ReadOnlyRegister4_Changed = function (stateChangedFunction) {
    this.serviceProperties.ReadOnlyRegister4.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ReadOnlyRegister5" property change events
* @method ReadOnlyRegister5_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.ReadOnlyRegister5_Changed = function (stateChangedFunction) {
    this.serviceProperties.ReadOnlyRegister5.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ReadOnlyRegister6" property change events
* @method ReadOnlyRegister6_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.ReadOnlyRegister6_Changed = function (stateChangedFunction) {
    this.serviceProperties.ReadOnlyRegister6.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ReadOnlyRegister7" property change events
* @method ReadOnlyRegister7_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestWidget.prototype.ReadOnlyRegister7_Changed = function (stateChangedFunction) {
    this.serviceProperties.ReadOnlyRegister7.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to SetReadWriteRegister
* @method SetReadWriteRegister
* @param {Int} RegisterIndex An action parameter
* @param {Int} RegisterValue An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestWidget.prototype.SetReadWriteRegister = function(RegisterIndex, RegisterValue, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetReadWriteRegister", this.url, this.domain, this.type, this.version);		
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
* A service action to GetWidgetClass
* @method GetWidgetClass
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestWidget.prototype.GetWidgetClass = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetWidgetClass", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["WidgetClass"] = Zapp.SoapRequest.readIntParameter(result["WidgetClass"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



