 

/**
* Service Proxy for linn.co.uk:Product:2
* @module Zapp
* @class Product
*/

var ServiceProduct = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Product-2/control";  // upnp control url
	this.domain = "linn.co.uk";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "Product";
	this.version = "2";
	this.serviceName = "linn.co.uk-Product-2";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["ProductType"] = new Zapp.ServiceProperty("ProductType");
	this.serviceProperties["ProductModel"] = new Zapp.ServiceProperty("ProductModel");
	this.serviceProperties["ProductName"] = new Zapp.ServiceProperty("ProductName");
	this.serviceProperties["ProductRoom"] = new Zapp.ServiceProperty("ProductRoom");
	this.serviceProperties["ProductStandby"] = new Zapp.ServiceProperty("ProductStandby");
	this.serviceProperties["ProductSourceIndex"] = new Zapp.ServiceProperty("ProductSourceIndex");
	this.serviceProperties["ProductSourceType"] = new Zapp.ServiceProperty("ProductSourceType");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceProduct.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServiceProduct.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "ProductType" property change events
* @method ProductType_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceProduct.prototype.ProductType_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductType.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ProductModel" property change events
* @method ProductModel_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceProduct.prototype.ProductModel_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductModel.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "ProductName" property change events
* @method ProductName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceProduct.prototype.ProductName_Changed = function (stateChangedFunction) {
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
ServiceProduct.prototype.ProductRoom_Changed = function (stateChangedFunction) {
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
ServiceProduct.prototype.ProductStandby_Changed = function (stateChangedFunction) {
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
ServiceProduct.prototype.ProductSourceIndex_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductSourceIndex.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "ProductSourceType" property change events
* @method ProductSourceType_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceProduct.prototype.ProductSourceType_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductSourceType.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* A service action to Type
* @method Type
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceProduct.prototype.Type = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Type", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.Model = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Model", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.Name = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Name", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.SetName = function(aName, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetName", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.Room = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Room", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.SetRoom = function(aRoom, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetRoom", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.Standby = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Standby", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.SetStandby = function(aStandby, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStandby", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.SourceCount = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceCount", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.SourceIndex = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceIndex", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.SetSourceIndex = function(aSourceIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetSourceIndex", this.url, this.domain, this.type, this.version);		
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
ServiceProduct.prototype.SourceType = function(aSourceIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceType", this.url, this.domain, this.type, this.version);		
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



