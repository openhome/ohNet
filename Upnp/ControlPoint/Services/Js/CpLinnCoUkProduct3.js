 

/**
* Service Proxy for CpProxyLinnCoUkProduct3
* @module Zapp
* @class Product
*/
	
var CpProxyLinnCoUkProduct3 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Product-3/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Product";
	this.version = "3";
	this.serviceName = "linn.co.uk-Product-3";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["ProductType"] = new Zapp.ServiceProperty("ProductType","string");
	this.serviceProperties["ProductModel"] = new Zapp.ServiceProperty("ProductModel","string");
	this.serviceProperties["ProductName"] = new Zapp.ServiceProperty("ProductName","string");
	this.serviceProperties["ProductRoom"] = new Zapp.ServiceProperty("ProductRoom","string");
	this.serviceProperties["ProductStandby"] = new Zapp.ServiceProperty("ProductStandby","bool");
	this.serviceProperties["ProductSourceIndex"] = new Zapp.ServiceProperty("ProductSourceIndex","int");
	this.serviceProperties["ProductSourceCount"] = new Zapp.ServiceProperty("ProductSourceCount","int");
	this.serviceProperties["ProductSourceXml"] = new Zapp.ServiceProperty("ProductSourceXml","string");
	this.serviceProperties["StartupSourceIndex"] = new Zapp.ServiceProperty("StartupSourceIndex","int");
	this.serviceProperties["StartupSourceEnabled"] = new Zapp.ServiceProperty("StartupSourceEnabled","bool");
	this.serviceProperties["ProductAnySourceName"] = new Zapp.ServiceProperty("ProductAnySourceName","int");
	this.serviceProperties["ProductAnySourceVisible"] = new Zapp.ServiceProperty("ProductAnySourceVisible","int");
	this.serviceProperties["ProductAnySourceType"] = new Zapp.ServiceProperty("ProductAnySourceType","int");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkProduct3.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkProduct3.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}


	

/**
* Adds a listener to handle "ProductType" property change events
* @method ProductType_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct3.prototype.ProductType_Changed = function (stateChangedFunction) {
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
CpProxyLinnCoUkProduct3.prototype.ProductModel_Changed = function (stateChangedFunction) {
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
CpProxyLinnCoUkProduct3.prototype.ProductName_Changed = function (stateChangedFunction) {
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
CpProxyLinnCoUkProduct3.prototype.ProductRoom_Changed = function (stateChangedFunction) {
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
CpProxyLinnCoUkProduct3.prototype.ProductStandby_Changed = function (stateChangedFunction) {
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
CpProxyLinnCoUkProduct3.prototype.ProductSourceIndex_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductSourceIndex.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProductSourceCount" property change events
* @method ProductSourceCount_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct3.prototype.ProductSourceCount_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductSourceCount.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProductSourceXml" property change events
* @method ProductSourceXml_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct3.prototype.ProductSourceXml_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductSourceXml.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "StartupSourceIndex" property change events
* @method StartupSourceIndex_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct3.prototype.StartupSourceIndex_Changed = function (stateChangedFunction) {
    this.serviceProperties.StartupSourceIndex.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "StartupSourceEnabled" property change events
* @method StartupSourceEnabled_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct3.prototype.StartupSourceEnabled_Changed = function (stateChangedFunction) {
    this.serviceProperties.StartupSourceEnabled.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readBoolParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProductAnySourceName" property change events
* @method ProductAnySourceName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct3.prototype.ProductAnySourceName_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductAnySourceName.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProductAnySourceVisible" property change events
* @method ProductAnySourceVisible_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct3.prototype.ProductAnySourceVisible_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductAnySourceVisible.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}
	

/**
* Adds a listener to handle "ProductAnySourceType" property change events
* @method ProductAnySourceType_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyLinnCoUkProduct3.prototype.ProductAnySourceType_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductAnySourceType.addListener(function (state) 
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
CpProxyLinnCoUkProduct3.prototype.Type = function(successFunction, errorFunction){	
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
CpProxyLinnCoUkProduct3.prototype.Model = function(successFunction, errorFunction){	
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
CpProxyLinnCoUkProduct3.prototype.Name = function(successFunction, errorFunction){	
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
CpProxyLinnCoUkProduct3.prototype.SetName = function(aName, successFunction, errorFunction){	
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
CpProxyLinnCoUkProduct3.prototype.Room = function(successFunction, errorFunction){	
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
CpProxyLinnCoUkProduct3.prototype.SetRoom = function(aRoom, successFunction, errorFunction){	
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
CpProxyLinnCoUkProduct3.prototype.Standby = function(successFunction, errorFunction){	
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
CpProxyLinnCoUkProduct3.prototype.SetStandby = function(aStandby, successFunction, errorFunction){	
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
CpProxyLinnCoUkProduct3.prototype.SourceCount = function(successFunction, errorFunction){	
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
* A service action to SourceXml
* @method SourceXml
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SourceXml = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceXml", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aSourceXml"] = Zapp.SoapRequest.readStringParameter(result["aSourceXml"]);	
	
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
CpProxyLinnCoUkProduct3.prototype.SourceIndex = function(successFunction, errorFunction){	
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
CpProxyLinnCoUkProduct3.prototype.SetSourceIndex = function(aSourceIndex, successFunction, errorFunction){	
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
* A service action to SetSourceIndexByName
* @method SetSourceIndexByName
* @param {String} aSourceName An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SetSourceIndexByName = function(aSourceName, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetSourceIndexByName", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aSourceName", aSourceName);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStartupSourceIndexByName
* @method SetStartupSourceIndexByName
* @param {String} aSourceName An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SetStartupSourceIndexByName = function(aSourceName, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStartupSourceIndexByName", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aSourceName", aSourceName);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to StartupSourceIndex
* @method StartupSourceIndex
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.StartupSourceIndex = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StartupSourceIndex", this.url, this.domain, this.type, this.version);		
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
* A service action to SetStartupSourceIndex
* @method SetStartupSourceIndex
* @param {Int} aSourceIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SetStartupSourceIndex = function(aSourceIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStartupSourceIndex", this.url, this.domain, this.type, this.version);		
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
* A service action to StartupSourceEnabled
* @method StartupSourceEnabled
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.StartupSourceEnabled = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("StartupSourceEnabled", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aStartupSourceEnabled"] = Zapp.SoapRequest.readBoolParameter(result["aStartupSourceEnabled"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetStartupSourceEnabled
* @method SetStartupSourceEnabled
* @param {Boolean} aStartupSourceEnabled An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SetStartupSourceEnabled = function(aStartupSourceEnabled, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetStartupSourceEnabled", this.url, this.domain, this.type, this.version);		
    request.writeBoolParameter("aStartupSourceEnabled", aStartupSourceEnabled);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SourceSystemName
* @method SourceSystemName
* @param {Int} aSourceIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SourceSystemName = function(aSourceIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceSystemName", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aSourceIndex", aSourceIndex);
    request.send(function(result){
		result["aSourceName"] = Zapp.SoapRequest.readStringParameter(result["aSourceName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SourceName
* @method SourceName
* @param {Int} aSourceIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SourceName = function(aSourceIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceName", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aSourceIndex", aSourceIndex);
    request.send(function(result){
		result["aSourceName"] = Zapp.SoapRequest.readStringParameter(result["aSourceName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetSourceName
* @method SetSourceName
* @param {Int} aSourceIndex An action parameter
* @param {String} aSourceName An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SetSourceName = function(aSourceIndex, aSourceName, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetSourceName", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aSourceIndex", aSourceIndex);
    request.writeStringParameter("aSourceName", aSourceName);
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
CpProxyLinnCoUkProduct3.prototype.SourceType = function(aSourceIndex, successFunction, errorFunction){	
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


/**
* A service action to SourceVisible
* @method SourceVisible
* @param {Int} aSourceIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SourceVisible = function(aSourceIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SourceVisible", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aSourceIndex", aSourceIndex);
    request.send(function(result){
		result["aSourceVisible"] = Zapp.SoapRequest.readBoolParameter(result["aSourceVisible"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetSourceVisible
* @method SetSourceVisible
* @param {Int} aSourceIndex An action parameter
* @param {Boolean} aSourceVisible An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkProduct3.prototype.SetSourceVisible = function(aSourceIndex, aSourceVisible, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetSourceVisible", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aSourceIndex", aSourceIndex);
    request.writeBoolParameter("aSourceVisible", aSourceVisible);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



