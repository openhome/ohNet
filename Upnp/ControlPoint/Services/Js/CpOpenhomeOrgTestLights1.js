 

/**
* Service Proxy for CpProxyOpenhomeOrgTestLights1
* @module ohNet
* @class TestLights
*/
	
var CpProxyOpenhomeOrgTestLights1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/openhome.org-TestLights-1/control";  // upnp control url
	this.domain = "openhome-org";
	this.type = "TestLights";
	this.version = "1";
	this.serviceName = "openhome.org-TestLights-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyOpenhomeOrgTestLights1.prototype.subscribe = function (serviceAddedFunction) {
    OhNet.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyOpenhomeOrgTestLights1.prototype.unsubscribe = function () {
    OhNet.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* A service action to GetCount
* @method GetCount
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetCount = function(successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetCount", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Count"] = OhNet.SoapRequest.readIntParameter(result["Count"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetRoom
* @method GetRoom
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetRoom = function(Index, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetRoom", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.send(function(result){
		result["RoomName"] = OhNet.SoapRequest.readStringParameter(result["RoomName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetName
* @method GetName
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetName = function(Index, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetName", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.send(function(result){
		result["FriendlyName"] = OhNet.SoapRequest.readStringParameter(result["FriendlyName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetPosition
* @method GetPosition
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetPosition = function(Index, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetPosition", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.send(function(result){
		result["X"] = OhNet.SoapRequest.readIntParameter(result["X"]);	
		result["Y"] = OhNet.SoapRequest.readIntParameter(result["Y"]);	
		result["Z"] = OhNet.SoapRequest.readIntParameter(result["Z"]);	
	
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
* @param {Int} Index An action parameter
* @param {Int} Color An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.SetColor = function(Index, Color, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("SetColor", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.writeIntParameter("Color", Color);
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
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetColor = function(Index, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetColor", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.send(function(result){
		result["Color"] = OhNet.SoapRequest.readIntParameter(result["Color"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetColorComponents
* @method GetColorComponents
* @param {Int} Color An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetColorComponents = function(Color, successFunction, errorFunction){	
	var request = new OhNet.SoapRequest("GetColorComponents", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Color", Color);
    request.send(function(result){
		result["Brightness"] = OhNet.SoapRequest.readIntParameter(result["Brightness"]);	
		result["Red"] = OhNet.SoapRequest.readIntParameter(result["Red"]);	
		result["Green"] = OhNet.SoapRequest.readIntParameter(result["Green"]);	
		result["Blue"] = OhNet.SoapRequest.readIntParameter(result["Blue"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



