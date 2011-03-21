 

/**
* Service Proxy for CpProxyLinnCoUkProduct2
* @module Zapp
* @class Product
*/
	
var CpProxyLinnCoUkProduct2 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Product-2/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Product";
	this.version = "2";
	this.serviceName = "linn.co.uk-Product-2";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["ProductName"] = new Zapp.ServiceProperty("ProductName","string");
	this.serviceProperties["ProductRoom"] = new Zapp.ServiceProperty("ProductRoom","string");
	this.serviceProperties["ProductStandby"] = new Zapp.ServiceProperty("ProductStandby","bool");
	this.serviceProperties["ProductSourceIndex"] = new Zapp.ServiceProperty("ProductSourceIndex","int");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkProduct2.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkProduct2.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "ProductName" property change events
* @method ProductName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct2.prototype.ProductName_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductName.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProductRoom" property change events
* @method ProductRoom_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct2.prototype.ProductRoom_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductRoom.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProductStandby" property change events
* @method ProductStandby_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct2.prototype.ProductStandby_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductStandby.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProductSourceIndex" property change events
* @method ProductSourceIndex_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct2.prototype.ProductSourceIndex_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductSourceIndex.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to Type
* @method Type
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.Type = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Type", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aType"] = Zapp.SoapRequest.readStringParameter(result["aType"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Model
* @method Model
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.Model = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Model", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aModel"] = Zapp.SoapRequest.readStringParameter(result["aModel"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Name
* @method Name
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.Name = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Name", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aName"] = Zapp.SoapRequest.readStringParameter(result["aName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetName
* @method SetName
* @param {String} aName An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.SetName = function(aName, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetName", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("aName", aName);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Room
* @method Room
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.Room = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Room", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aRoom"] = Zapp.SoapRequest.readStringParameter(result["aRoom"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetRoom
* @method SetRoom
* @param {String} aRoom An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.SetRoom = function(aRoom, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetRoom", this.url, this.formattedDomain, this.type, this.version);		
    request.writeStringParameter("aRoom", aRoom);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to Standby
* @method Standby
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.Standby = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Standby", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aStandby"] = Zapp.SoapRequest.readBoolParameter(result["aStandby"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStandby
* @method SetStandby
* @param {Boolean} aStandby An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.SetStandby = function(aStandby, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStandby", this.url, this.formattedDomain, this.type, this.version);		
    request.writeBoolParameter("aStandby", aStandby);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SourceCount
* @method SourceCount
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.SourceCount = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceCount", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aSourceCount"] = Zapp.SoapRequest.readIntParameter(result["aSourceCount"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SourceIndex
* @method SourceIndex
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.SourceIndex = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceIndex", this.url, this.formattedDomain, this.type, this.version);		
    request.send(function(result){
		result["aSourceIndex"] = Zapp.SoapRequest.readIntParameter(result["aSourceIndex"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetSourceIndex
* @method SetSourceIndex
* @param {Int} aSourceIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.SetSourceIndex = function(aSourceIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetSourceIndex", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("aSourceIndex", aSourceIndex);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SourceType
* @method SourceType
* @param {Int} aSourceIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct2.prototype.SourceType = function(aSourceIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceType", this.url, this.formattedDomain, this.type, this.version);		
    request.writeIntParameter("aSourceIndex", aSourceIndex);
    request.send(function(result){
		result["aSourceType"] = Zapp.SoapRequest.readStringParameter(result["aSourceType"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



